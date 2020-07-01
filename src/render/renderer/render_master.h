#ifndef LABO_RENDER_MASTER_H
#define LABO_RENDER_MASTER_H

#include <SFML/Graphics.hpp>
#include "../camera.h"
#include "sky_box_renderer.h"
#include "triangle_renderer.h"
#include "moving_triangle_renderer.h"
#include "text_renderer.h"
#include "chunk_renderer.h"
#include "flora_renderer.h"
#include "water_renderer.h"
#include "../mesh/entity_mesh.h"
#include "entity_renderer.h"

namespace labo::render{
class RenderMaster {
public:
  /**
   * Chunkを描画する
   */
  void drawChunk(const SubChunkMeshCollection &collection);

  void drawEntity(const EntityRenderInfo &renderInfo);

  void finish(sf::Window &window, const Camera &camera, float elapsedTime);


private:
  MovingTriangleRenderer movingTriangleRenderer;
  ChunkRenderer chunkRenderer;
  EntityRenderer entityRenderer;
  FloraRenderer floraRenderer;
  WaterRenderer waterRenderer;
  SkyBoxRenderer skyBoxRenderer;
  TriangleRenderer triangleRenderer;
  TextRenderer textRenderer;

};
}

#endif //LABO_RENDER_MASTER_H
