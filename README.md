# Ogiwara Labo
自作Minecraftと自作物理エンジン

# Getting start
- cmakeを入れる
- submoduleをinstall
- `cd cmake-build-debug && cmake ..`

# NOTE
多層アーキテクチャ
App -> Render -> Minecraft -> Physics -> Math

App: Application, Config, SFML, Window Manager
Render: OpenGL, Camera
Minecraft: Player, Level, Entity, Event
Physics: AABB
Math: glm, Noise, Random, or other utility

# Coding rule
ファイル名はsnake_came
メンバはcamelCase

PMMPのコードを積極的に真似ていこう

Level holds for player.