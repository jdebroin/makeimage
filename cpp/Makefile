# Generate and view image:
# make
# ./makeimage
# display out.bmp

# Profile:
# g++ -o $@ $^ -pg
# g++ -g -c -o $@ $< -pg
# make
# ./makeimage
# gprof makeimage > gprof.out

INCS = Drawing.h
OBJS = makeimage.o Drawing.o

makeimage: $(OBJS)
	g++ -o $@ $^

%.o: %.cpp $(INCS)
	g++ -c -o $@ $<

.PHONY: clean

clean:
	rm -f makeimage $(OBJS)
