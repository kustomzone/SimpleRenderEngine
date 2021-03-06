//
// Created by morten on 04/08/16.
//

#include "SRE/Debug.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/impl/GL.hpp"

#include <vector>
#include <iostream>
#include <SRE/Texture.hpp>

using namespace std;

namespace SRE {

    glm::vec4 Debug::color = glm::vec4(1,0,1,1);

    glm::vec4 Debug::getColor(){
        return color;
    }

    void Debug::setColor(glm::vec4 color){
        Debug::color = color;
    }

    void Debug::drawLine(glm::vec3 from, glm::vec3 to){
		vector<glm::vec3> verts;
		verts.push_back(from);
		verts.push_back(to);
		vector<glm::vec3> normals;
		vector<glm::vec2> uvs;

		Mesh mesh(verts, normals, uvs,MeshTopology::Lines);

        Shader* shader = Shader::getUnlit();
        shader->set("color", color);
        shader->set("tex", Texture::getWhiteTexture());
        if (SimpleRenderEngine::instance != nullptr){
            SimpleRenderEngine::instance->draw(&mesh, glm::mat4(1),shader);
        }
    }

    void Debug::drawLineStrip(std::vector<glm::vec3> &&verts) {
        std::vector<glm::vec3> v{verts};
        drawLineStrip(v);
    }

    void Debug::drawLineStrip(std::vector<glm::vec3> &verts) {
        vector<glm::vec3> normals;
        vector<glm::vec2> uvs;

        Mesh mesh(verts, normals, uvs, MeshTopology::LineStrip);

        Shader* shader = Shader::getUnlit();
        shader->set("color", color);
        shader->set("tex", Texture::getWhiteTexture());
        if (SimpleRenderEngine::instance != nullptr){
            SimpleRenderEngine::instance->draw(&mesh, glm::mat4(1),shader);
        }
    }

    void Debug::checkGLError() {
        for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
        {
            //Process/log the error.
            switch (err){
                case GL_INVALID_ENUM:
                    std::cerr << "GL_INVALID_ENUM"<<std::endl;
                    break;
                case GL_INVALID_VALUE:
                    std::cerr << "GL_INVALID_VALUE"<<std::endl;
                    break;
                case GL_INVALID_OPERATION:
                    std::cerr << "GL_INVALID_OPERATION"<<std::endl;
                    break;
                case GL_OUT_OF_MEMORY:
                    std::cerr << "GL_OUT_OF_MEMORY"<<std::endl;
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION"<<std::endl;
                    break;

            }
        }
    }

}