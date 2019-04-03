PROJROOT = .
TEST = ${PROJROOT}/test.c
TESTBIN = ${PROJROOT}/rlsp
BUILDS = ${PROJROOT}/builds
SRCDIR = ${PROJROOT}/src
SRCLIB = ${PROJROOT}/srclib
# LIB = ${PROJROOT}/lib

default: clean compile build link

compile:
	@echo Compiling...
	@gcc -g -c ${SRCDIR}/*.c ${SRCLIB}/*.c ${TEST}
	@echo Compile Succeeded.
	@echo

build:
	@echo Making build directory...
	@-mkdir ${BUILDS}
	@-mv *.o ${BUILDS}/
	@echo

link:
	@echo Linking...
	@gcc -o ${TESTBIN} ${BUILDS}/*.o
	@echo Link Succeeded.
	@echo

test:
	${PROJROOT}/${TESTBIN}

clean:
	-rm -rf ${BUILDS}/
	-rm ${TESTBIN}
	@echo
