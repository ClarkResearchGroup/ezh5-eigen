CC = g++
CC_FLAGS = -O2 -DNDEBUG -std=c++11 -W -Wno-unused-parameter

# HDF5_INC = -I/usr/lib/x86_64-linux-gnu/hdf5/serial/include
# HDF5_LIB = -L/usr/lib/x86_64-linux-gnu/hdf5/serial/lib -lhdf5

HDF5_INC = -I/usr/local/opt/szip/include -I/usr/local/Cellar/hdf5/1.10.3/include
HDF5_LIB = -L/usr/local/Cellar/hdf5/1.10.3/lib /usr/local/Cellar/hdf5/1.10.3/lib/libhdf5_hl.a /usr/local/Cellar/hdf5/1.10.3/lib/libhdf5.a -L/usr/local/opt/szip/lib -lsz -lz -ldl -lm

EIGEN_INC = -I ${EIGEN3_INCLUDE_DIR}
#######

EXEC = example
SOURCES = $(wildcard ./../*.cc ./*.cc)
OBJECTS = $(SOURCES:.cc=.o)


# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CC_FLAGS) $(HDF5_LIB) -o $(EXEC)

# To obtain object files
%.o: %.cc
	$(CC) -c $(CC_FLAGS) $(HDF5_INC) $(EIGEN_INC) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
