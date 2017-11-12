
output: main.o Camera.o Individual.o Population.o ImageHandler.o 
	g++ main.o Camera.o Individual.o Population.o ImageHandler.o `pkg-config --cflags --libs opencv` -o output

main.o: main.cpp
	g++ -c main.cpp

Camera.o: camera/Camera.cpp camera/Camera.h
	g++ -c camera/Camera.cpp

Individual.o: genetic/Individual.cpp genetic/Individual.h
	g++ -c genetic/Individual.cpp

Population.o: genetic/Population.cpp genetic/Population.h
	g++ -c genetic/Population.cpp

ImageHandler.o: imageshandler/ImageHandler.cpp imageshandler/ImageHandler.h
	g++ -c imageshandler/ImageHandler.cpp

clean:
	rm *.o output
