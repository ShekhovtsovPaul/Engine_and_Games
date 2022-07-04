#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"

// EACH SPRITE in one VBO !!!
namespace Engine {

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	// a SINGLE SPRITE ! - need to SORT SPRITES !
	struct Glyph {

		float depth;	// front/behind diff sprites!

		GLuint texture;
		Vertex topLeft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;
	};

	// OFFSET to each VBO in VAO !
	class RenderBatch {
	public:
		
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :
			offset(Offset),
			numVertices(NumVertices),
			texture(Texture)
		{
		}

		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	// BOX of SPRITES !!! - BOX of all VERTICES in ONE VBO !!!
	class SpriteBatch {
	public:

		SpriteBatch();
		~SpriteBatch();

		void init();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);	// sort by default - CLEAR ALL
		void end();	// READ all VERTICES into one VBO !!!
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);	// position, dimention
		void renderBatch();

	private:

		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();	// REWRITE VECTOR of GLYPHS

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;
		
		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphs;	// SPRITES! pos, col, uv
		std::vector<RenderBatch> _renderBatches;	// offset, texture, vertices
	};

}

