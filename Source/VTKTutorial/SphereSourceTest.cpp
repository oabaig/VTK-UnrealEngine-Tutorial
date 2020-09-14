// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereSourceTest.h"
#include "Engine.h"

// Sets default values
ASphereSourceTest::ASphereSourceTest()
{
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	// New in UE 4.17, multi-threaded PhysX cooking.
	mesh->bUseAsyncCooking = true;
}

void ASphereSourceTest::PostActorCreated() {
	Super::PostActorCreated();
	GenerateSphere();
}

void ASphereSourceTest::PostLoad()
{
	Super::PostLoad();
	GenerateSphere();
}

void ASphereSourceTest::GenerateSphere() {
	// create the sphere using VTK by giving it a center and radius
	vtkSmartPointer<vtkSphereSource> sphereSource =
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetCenter(0.0, 0.0, 0.0);
	sphereSource->SetRadius(500.0);

	// smoothes out the sphere
	sphereSource->SetPhiResolution(100);
	sphereSource->SetThetaResolution(100);

	// update the sphere
	sphereSource->Update();

	// create poly data object to retrieve poly data from sphere source
	vtkSmartPointer<vtkPolyData> polyData =
		vtkSmartPointer<vtkPolyData>::New();

	// get output from sphere and put it into poly data object
	polyData = sphereSource->GetOutput();

	// optional code ~ have to include Engine.h
	// output number of points
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green,
		TEXT("Number of Points: ") + FString::SanitizeFloat(polyData->GetNumberOfPoints()));

	// optional code 
	// opens the message log for ouput
	auto messageLog = FMessageLog("Points");
	messageLog.Open(EMessageSeverity::Info, true);

	TArray<FLinearColor> verticeColors;

	// optional - output all points to message log
	// store all the points into a vvector containing all the vertices
	double x[3];
	TArray<FVector> vertices;
	for (vtkIdType i = 0; i < polyData->GetNumberOfPoints(); i++) {
		// get point from poly data and store in vertice
		polyData->GetPoint(i, x);
		vertices.Add(FVector(x[0], x[1], x[2]));

		verticeColors.Add(FLinearColor(255, 255, 255, 255));

		// optional - output point to message log
		messageLog.Message(EMessageSeverity::Info,
			FText::FromString(FString::Printf(TEXT("Point %d: (%f, %f, %f)"), i, x[0], x[1], x[2])));
	}

	// create a cell array data to get all the polygons from the polygon data
	vtkSmartPointer<vtkCellArray> cellArray =
		vtkSmartPointer<vtkCellArray>::New();

	// get polygon data and store into array
	cellArray = polyData->GetPolys();

	// optional - output number of triangles
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue,
		TEXT("Number of Vertices: ") + FString::SanitizeFloat(cellArray->GetSize()));

	// stores the data for triangles
	TArray<int32> Triangles;

	// create a list that stores the points, in order, for each triangle
	// get each vertice and add it into a triangles vector in order
	vtkSmartPointer<vtkIdList> p =
		vtkSmartPointer<vtkIdList>::New();
	int h;
	for (int i = 0; i < polyData->GetNumberOfPolys(); i++) {
		// GetNextCell returns 0 if end of cells, 1 otherwise
		h = cellArray->GetNextCell(p);
		if (h == 0) {
			break;
		}

		// if the number of vertices in p is 3
		if (p->GetNumberOfIds() == 3) {
			Triangles.Add(p->GetId(0));
			Triangles.Add(p->GetId(1));
			Triangles.Add(p->GetId(2));
		}
	}

	// draws the vertices and triangles in Unreal
	// most of the fields are unused for the purpose of this project, so just create empty arrays
	mesh->CreateMeshSection_LinearColor(0, vertices, Triangles, 
		TArray<FVector>(), TArray<FVector2D>(), verticeColors, TArray<FProcMeshTangent>(), true);

	// Enable collision data
	mesh->ContainsPhysicsTriMeshData(true);
}
