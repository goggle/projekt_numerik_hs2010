CC = g++
OBJS = vector.o matrix2.o matrix3.o dataparser.o element.o vertex.o edge.o matrixentry.o sparsematrix.o fesolver.o rgb.o imgtriangle.o colormap.o image.o
DEBUG = -O3 -DNDEBUG #-g -DNDEBUG
CFLAGS = -Wall -c $(DEBUG) 
LFLAGS = -Wall $(DEBUG)

all: $(OBJS)
#	$(CC) $(LFLAGS) main.cpp $(OBJS) -o prog
#	$(CC) $(LFLAGS) parsertest.cpp $(OBJS) -o parsertest
#	$(CC) $(LFLAGS) sparsetest.cpp $(OBJS) -o sparsetest
	$(CC) $(LFLAGS) -lpng -lz numsimulation_fein.cpp $(OBJS) -o ../bin/numSimulation_fein
	$(CC) $(LFLAGS) -lpng -lz numsimulation_grob.cpp $(OBJS) -o ../bin/numSimulation_grob
#	$(CC) $(LFLAGS) plotgitter.cpp $(OBJS) -o plotGitterData 
	#$(CC) image.o $(OBJS) $(LFLAGS) -lpng -lz -o test plot/test.cpp
	$(CC) $(LFLAGS) -lpng -lz plot/test.cpp $(OBJS) -o test

vector.o: vector.h vector.cpp element.o edge.o
	$(CC) $(CFLAGS) vector.cpp

matrix2.o: matrix2.h matrix2.cpp
	$(CC) $(CFLAGS) matrix2.cpp

matrix3.o: matrix3.h matrix3.cpp
	$(CC) $(CFLAGS) matrix3.cpp

vertex.o: vertex.h vertex.cpp
	$(CC) $(CFLAGS) vertex.cpp

element.o: element.h element.cpp vertex.o
	$(CC) $(CFLAGS) element.cpp

edge.o: edge.h edge.cpp vertex.o
	$(CC) $(CFLAGS) edge.cpp

dataparser.o: dataparser.h dataparser.cpp element.o edge.o vertex.o
	$(CC) $(CFLAGS) dataparser.cpp

matrixentry.o: matrixentry.h matrixentry.cpp
	$(CC) $(CFLAGS) matrixentry.cpp

sparsematrix.o: sparsematrix.h sparsematrix.cpp matrixentry.o matrix3.o element.o vector.o edge.o
	$(CC) $(CFLAGS) sparsematrix.cpp

fesolver.o: fesolver.h fesolver.cpp vector.o matrix2.o vertex.o element.o dataparser.o matrixentry.o sparsematrix.o matrix2.o matrix3.o image.o colormap.o rgb.o imgtriangle.o
	$(CC) $(CFLAGS) fesolver.cpp

rgb.o: plot/rgb.h plot/rgb.cpp
	$(CC) $(CFLAGS) plot/rgb.cpp

imgtriangle.o: plot/imgtriangle.h plot/imgtriangle.cpp rgb.o
	$(CC) $(CFLAGS) plot/imgtriangle.cpp
	
image.o: plot/image.h plot/image.cpp rgb.o imgtriangle.o colormap.o
	$(CC) $(CFLAGS) plot/image.cpp 

colormap.o: plot/colormap.h plot/colormap.cpp rgb.o
	$(CC) $(CFLAGS) plot/colormap.cpp


clean:
	rm -f *.o prog parsertest sparsetest fetest plotGitterData ../bin/numSimulation_fein ../bin/numSimulation_grob ../data/u_fein.dat ../data/u_grob.dat test
