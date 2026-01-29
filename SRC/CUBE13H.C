#include "vec.h"
#include "mat.h"
#include "math.h"
#include "vga.h"
#include "tringl.h"
#include "keybrd.h"
#include "renderer.h"

#define WIDTH 320
#define HEIGHT 200
#define HALF_WIDTH 160
#define HALF_HEIGHT 100
#define FOV_FACTOR 280
#define VERTEX_COUNT 8
#define FACE_COUNT 12

static Vec3 cubeRot;
static Vec3 cameraPos;
static TriArray triangles;
static int isRunning;

static const Face faces[FACE_COUNT] = {
    // front
    {1, 2, 3, 0x50, {0, 0, -1}},
    {1, 3, 4, 0x51, {0, 0, -1}},
    // right
    {4, 3, 5, 0x40, {1, 0, 0}},
    {4, 5, 6, 0x41, {1, 0, 0}},
    // back
    {6, 5, 7, 0x22, {0, 0, 1}},
    {6, 7, 8, 0x23, {0, 0, 1}},
    // left
    {8, 7, 2, 0x2A, {-1, 0, 0}},
    {8, 2, 1, 0x2B, {-1, 0, 0}},
    // top
    {2, 7, 5, 0x28, {0, 1, 0}},
    {2, 5, 3, 0x29, {0, 1, 0}},
    // bottom
    {6, 8, 1, 0x36, {0, -1, 0}},
    {6, 1, 4, 0x37, {0, -1, 0}},
};

static const Vec3 vertices[VERTEX_COUNT] = {
    {-1, -1, -1},
    {-1,  1, -1},
    { 1,  1, -1},
    { 1, -1, -1},
    { 1,  1,  1},
    { 1, -1,  1},
    {-1,  1,  1},
    {-1, -1,  1},
};

static void processInput(void) {
    if (kbHit(ESC)) {
        isRunning = 0;
    } else if (kbHit(W)) {
        cameraPos.z -= 0.1; 
    } else if (kbHit(S)) {
        cameraPos.z += 0.1; 
    } else if (kbHit(A)) {
        cameraPos.x += 0.1; 
    } else if (kbHit(D)) {
        cameraPos.x -= 0.1;
    } else if (kbHit(U_ARROW)) {
        cameraPos.y += 0.1;
    } else if (kbHit(D_ARROW)) {
        cameraPos.y -= 0.1;
    }
}

static void update(void) {
    int i, j;
    Vec3 cameraRay;
    Vec3 faceVertices[3];
    Vec3 transformedVertices[VERTEX_COUNT];
    Mat3 rotMat, tempMat, rotMatx, rotMaty, rotMatz;
    Triangle projectedTriangle;
    
    vecSAdd(&cubeRot, 0.02);

    if (cubeRot.x >= TWO_PI) cubeRot.x -= TWO_PI;
    if (cubeRot.y >= TWO_PI) cubeRot.y -= TWO_PI;
    if (cubeRot.z >= TWO_PI) cubeRot.z -= TWO_PI;

    mtxRotx(&rotMatx, cubeRot.x);
    mtxRoty(&rotMaty, cubeRot.y);
    mtxRotz(&rotMatz, cubeRot.z);

    mtxMulMat3(&tempMat, &rotMatx, &rotMaty);
    mtxMulMat3(&rotMat, &tempMat, &rotMatz);

    for (i = 0; i < VERTEX_COUNT; i++) {
        Vec3 transformedVertex;
        const Vec3 vertex = vertices[i];

        // Rotate the vertex around the cube's center
        mtxMulVec3(&transformedVertex, &rotMat, &vertex);

        // Translate the vertex away from the camera
        transformedVertex.z = transformedVertex.z - cameraPos.z;

        // Save transformed vertex in the array of transformed vertices
        transformedVertices[i] = transformedVertex;
    }

    for (i = 0; i < FACE_COUNT; i++) {
        Vec3 transformedNormal;
        const Face face = faces[i];

        // Rotate the face normal
        mtxMulVec3(&transformedNormal, &rotMat, &face.normal);

        faceVertices[0] = transformedVertices[face.a - 1];
        faceVertices[1] = transformedVertices[face.b - 1];
        faceVertices[2] = transformedVertices[face.c - 1];

        vecSub(&cameraRay, &cameraPos, &faceVertices[0]);

        // Backface Culling
        if (vecDot(&transformedNormal, &cameraRay) < 0) 
            continue;

        for (j = 0; j < 3; ++j) {
            Vec2 pv;
            Vec3 cameraView;
            const Vec3 fv = faceVertices[j];
            
            // Convert points to camera's local coordinate system
            vecSub(&cameraView, &fv, &cameraPos);
            
            // Project the points onto the screen
            vecProject(&pv, &cameraView, FOV_FACTOR);
            pv.x += HALF_WIDTH;
            pv.y += HALF_HEIGHT;
            
            projectedTriangle.points[j] = pv;
        }

        projectedTriangle.color = face.color;
        
		taPushback(&triangles, &projectedTriangle);
    }    
}

static void render(void) {
    int i;

    vgaClearOffscreen(0x0);

    for (i = 0; i < triangles.count; i++) {
        const Triangle* tri = taAt(&triangles, i);

        // Draw filled triangle
        rndDrawFilledTri(
            tri->points[0].x, tri->points[0].y, // vertex A
            tri->points[1].x, tri->points[1].y, // vertex B
            tri->points[2].x, tri->points[2].y, // vertex C
            tri->color
        );  
    }

   	taClear(&triangles);

    vgaUpdateVram();
}

void main(void) {
    cameraPos.x = 0.0;
    cameraPos.y = 0.0;
	cameraPos.z = 5.0;
    
    cubeRot.x = 0.0;
    cubeRot.y = 0.0;
    cubeRot.z = 0.0;
    
    isRunning = 1;

    vgaInit();
    kbInit();

	taInit(&triangles, 2);
    initSinCosLUT();
    
	while (isRunning) {
        processInput();
        update();
        render();
    }

	taFree(&triangles);

    vgaExit();
    kbExit();
}
