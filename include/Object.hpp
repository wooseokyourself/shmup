#ifndef __OBJECT__
#define __OBJECT__

#include <iostream>
#include <string>
#include <vector>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "World.hpp"

class Object {
public:
    Object (std::string path) {
        scene = aiImportFile(path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
        if (scene)
            std::cout << "model load done" << std::endl;
    }

    void draw () {
        drawMeshes(scene, scene->mRootNode);
    }

private:
    void drawMeshes (const aiScene* sc, const aiNode* nd) {
        unsigned int i;
        unsigned int n = 0, t;
        aiMatrix4x4 m = nd->mTransformation;

        /* update transform */
        aiTransposeMatrix4(&m);
        glPushMatrix();
        glMultMatrixf((float*)&m);

        /* draw all meshes assigned to this node */
        for (; n < nd->mNumMeshes; ++n) {
            const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

            apply_material(sc->mMaterials[mesh->mMaterialIndex]);

            if(mesh->mNormals == NULL) {
                glDisable(GL_LIGHTING);
            } else {
                glEnable(GL_LIGHTING);
            }

            for (t = 0; t < mesh->mNumFaces; ++t) {
                const aiFace* face = &mesh->mFaces[t];
                GLenum face_mode;

                switch(face->mNumIndices) {
                    case 1: face_mode = GL_POINTS; break;
                    case 2: face_mode = GL_LINES; break;
                    case 3: face_mode = GL_TRIANGLES; break;
                    default: face_mode = GL_POLYGON; break;
                }

                glBegin(face_mode);

                for(i = 0; i < face->mNumIndices; i++) {
                    int index = face->mIndices[i];
                    if(mesh->mColors[0] != NULL)
                        glColor4fv((GLfloat*)&mesh->mColors[0][index]);
                    if(mesh->mNormals != NULL)
                        glNormal3fv(&mesh->mNormals[index].x);
                    glVertex3fv(&mesh->mVertices[index].x);
                }

                glEnd();
            }

        }

        /* draw all children */
        for (n = 0; n < nd->mNumChildren; ++n) {
            drawMeshes(sc, nd->mChildren[n]);
        }

        glPopMatrix();
    }

void apply_material(const aiMaterial *mtl) {
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	aiColor4D diffuse;
	aiColor4D specular;
	aiColor4D ambient;
	aiColor4D emission;
	ai_real shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;

	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	if(ret1 == AI_SUCCESS) {
    	max = 1;
    	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
		if(ret2 == AI_SUCCESS)
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
        else
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    }
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);
}

void color4_to_float4(const C_STRUCT aiColor4D *c, float f[4]) {
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void set_float4(float f[4], float a, float b, float c, float d) {
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}


private:
    const aiScene* scene;
};

#endif