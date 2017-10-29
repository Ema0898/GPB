
output: main.o GameEntity.o Texture.o AnimatedTexture.o Game.o Level.o Graphics.o PlayScreen.o StartScreen.o AssetManager.o AudioManager.o InputManager.o ScreenManager.o Player.o BackgroundStars.o StarLayer.o Star.o Timer.o AStar.o Grid.o TIEFighter.o
	g++ main.o GameEntity.o Texture.o AnimatedTexture.o Game.o Level.o Graphics.o PlayScreen.o StartScreen.o AssetManager.o AudioManager.o InputManager.o ScreenManager.o Player.o BackgroundStars.o StarLayer.o Star.o Timer.o AStar.o Grid.o TIEFighter.o `pkg-config --cflags --libs sdl2` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o output

main.o: main.cpp
	g++ -c main.cpp

GameEntity.o: entities/GameEntity.cpp entities/GameEntity.h
	g++ -c entities/GameEntity.cpp

Texture.o: entities/Texture.cpp entities/Texture.h
	g++ -c entities/Texture.cpp

AnimatedTexture.o: entities/AnimatedTexture.cpp entities/AnimatedTexture.h
	g++ -c entities/AnimatedTexture.cpp

Game.o: game/Game.cpp game/Game.h
	g++ -c game/Game.cpp

Level.o: game/Level.cpp game/Level.h
	g++ -c game/Level.cpp

Graphics.o: graphics/Graphics.cpp graphics/Graphics.h
	g++ -c graphics/Graphics.cpp

PlayScreen.o: graphics/PlayScreen.cpp graphics/PlayScreen.h
	g++ -c graphics/PlayScreen.cpp

StartScreen.o: graphics/StartScreen.cpp graphics/StartScreen.h
	g++ -c graphics/StartScreen.cpp

AssetManager.o: managers/AssetManager.cpp managers/AssetManager.h
	g++ -c managers/AssetManager.cpp

AudioManager.o: managers/AudioManager.cpp managers/AudioManager.h
	g++ -c managers/AudioManager.cpp

InputManager.o: managers/InputManager.cpp managers/InputManager.h
	g++ -c managers/InputManager.cpp

ScreenManager.o: managers/ScreenManager.cpp managers/ScreenManager.h
	g++ -c managers/ScreenManager.cpp

Player.o: player/Player.cpp player/Player.h
	g++ -c player/Player.cpp

BackgroundStars.o: starbackground/BackgroundStars.cpp starbackground/BackgroundStars.h
	g++ -c starbackground/BackgroundStars.cpp

StarLayer.o: starbackground/StarLayer.cpp starbackground/StarLayer.h
	g++ -c starbackground/StarLayer.cpp

Star.o: starbackground/Star.cpp starbackground/Star.h
	g++ -c starbackground/Star.cpp

Timer.o: tools/Timer.cpp tools/Timer.h
	g++ -c tools/Timer.cpp

AStar.o: pathfinding/AStar.cpp pathfinding/AStar.h
	g++ -c pathfinding/AStar.cpp

Grid.o: pathfinding/Grid.cpp pathfinding/Grid.h
	g++ -c pathfinding/Grid.cpp

TIEFighter.o: enemies/TIEFighter.cpp enemies/TIEFighter.h
	g++ -c enemies/TIEFighter.cpp

clean:
	rm *.o output