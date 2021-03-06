ONESIDED_LIB=$(shell xmpf90 --show-env | sed -n '/ONESIDED_LIB=/p' | sed 's/ONESIDED_LIB=//' | sed "s/\"//g")

XFC     = xmpf90
XRUN    = mpiexec
TESTS = $(wildcard *.f90)
EXES  = $(TESTS:.f90=.x)
OBJS  = $(TESTS:.f90=.o)

.PHONY: clean all default run

all default: $(EXES)

.SUFFIXES: .x .f90

chk.o: ./chk/chk.f90
	$(XFC) -c $^ -o $@

FFLAG = 
ifeq ($(ONESIDED_LIB),MPI3)
        FFLAG = -cpp -D_MPI3
else
        FFLAG = -cpp
endif

%.x: %.f90 chk.o
	$(XFC) $(FFLAG) -o $@ $< ./chk.o

run: $(EXES)
	$(XRUN) -n 2 ./gmove_lc_2.x
	$(XRUN) -n 4 ./gmove_lc_4.x
	$(XRUN) -n 8 ./gmove_lc_8.x
	$(XRUN) -n 2 ./gmove_ata_2.x
	$(XRUN) -n 4 ./gmove_ata_4.x
	$(XRUN) -n 2 ./gmove_bca_2.x
	$(XRUN) -n 4 ./gmove_bca_4.x
	$(XRUN) -n 8 ./gmove_bca_8.x
	$(XRUN) -n 12 ./gmove_bca_12.x
	$(XRUN) -n 16 ./gmove_bca_16.x
	$(XRUN) -n 2 ./gmove_cp_2.x
	$(XRUN) -n 4 ./gmove_cp_4.x
	$(XRUN) -n 8 ./gmove_cp_8.x
	$(XRUN) -n 16 ./gmove_cp_16.x
	$(XRUN) -n 2 ./gmove_G2L_2.x
	$(XRUN) -n 4 ./gmove_G2L_4.x
	$(XRUN) -n 8 ./gmove_G2L_8.x
	$(XRUN) -n 16 ./gmove_G2L_16.x
	$(XRUN) -n 4 ./gmove_G2L_index.x
	$(XRUN) -n 2 ./gmove_inout_1.x
	$(XRUN) -n 8 ./gmove_inout_3.x
	$(XRUN) -n 2 ./484.x
	$(XRUN) -n 4 ./gmove_test_normal.x
	$(XRUN) -n 8 ./gmove_test_in.x
	$(XRUN) -n 8 ./gmove_test_out.x

clean:
	rm -f $(EXES) $(OBJS) _xmpf_module_INIT.o chk.o
