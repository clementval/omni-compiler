XFC     = xmpf90
XRUN    = mpiexec
EXES    = module_test.x module_test0.x arg.x dnodes.x refobj.x 228.x 358_result.x 383.x 377.x 392.x 397.x 412.x

all: module_test.x module_test0.x arg.x dnodes.x external.o interface.o xmp_lib.o threadprivate.o refobj.x \
     103.x 223.o 228.x 229.o 230.o 321.o 45_save.o 358_result.x 373.o 377.x 261.o 162.o 383.x 384.o 391.o 392.x 393.o 278\ spacefile.x derived.o func.o    schedule_default.o task001.o 152.x 397.x double_option.x nargs.o
###     103.x 223.o 228.x 229.o 230.o 321.o 45_save.o 358_result.x 373.o 377.x 261.o 162.o 383.x 384.o 391.o 392.x 393.o 278\ spacefile.x derived.o func.o save_desc.x schedule_default.o task001.o 152.x 397.x double_option.x nargs.o
###mpiexec -n 4 ./static_desc.x
###Fatal error in PMPI_Comm_split: Other MPI error, error stack:
###PMPI_Comm_split(495).................: MPI_Comm_split(comm=0xc4000000, color=1, key=1, new_comm=0xa990c0) failed
###PMPI_Comm_split(477).................: 
###MPIR_Comm_split_impl(249)............: 
###MPIR_Get_contextid_sparse_group(1193): Too many communicators (0/2048 free on this process; ignore_id=0)


.SUFFIXES: .x .o .f90

.f90.x:
	$(XFC) -o $@ $<

.f90.o:
	$(XFC) -c $<

.f.x:
	$(XFC) -o $@ $<

.f.o:
	$(XFC) -c $<

nargs.o: nargs.f90
	$(XFC) -c --Wn"-w" $<

double_option.x: double_option.f90
	$(XFC) -o double_option.x --Wn"-O2 -O2" double_option.f90

task001.o: task001.f90
	$(XFC) --openmp task001.f90 -c

schedule_default.o: schedule_default.F90
	$(XFC) --openmp schedule_default.F90 -c

278\ spacefile.x: 278\ spacefile.f90
	@rm -rf 278\ module
	mkdir 278\ module
	$(XFC) 278\ spacefile.f90 -J278\ module -o 278\ spacefile.x -cpp -DSTRING='"P A S S"'

module_test0.x: module0.o main.o
	$(XFC) -o module_test0.x module0.o main.o

module_test1.o: module_test2.o module_test1.f90
	$(XFC) -c module_test1.f90

module_test.x: module_test2.o module_test1.o
	$(XFC) -o module_test.x module_test2.o module_test1.o

module_test2.o: module_test2.f90
	$(XFC) -c module_test2.f90

module0.o: module0.f90
	rm -rf mod
	mkdir -p mod
	$(XFC) -c module0.f90 -Jmod

external.o: external.f90
	$(XFC) -c external.f90

main.o: main.f90 module0.o
	$(XFC) -c main.f90 -Jmod

arg.x: arg.o
	$(XFC) -o arg.x arg.o

arg.o: arg.f90
	$(XFC) -c arg.f90

dnodes.x: dnodes.o
	$(XFC) -o dnodes.x dnodes.o

dnodes.o: dnodes.f90
	$(XFC) -c dnodes.f90

interface.o: interface.f90
	$(XFC) -c interface.f90

xmp_lib.o: xmp_lib.f90
	$(XFC) -c xmp_lib.f90

threadprivate.o: threadprivate.f90
	$(XFC) -c --openmp threadprivate.f90

refobj.x: refobj.f90
	$(XFC) -o refobj.x refobj.f90

228.x: 228.f
	$(XFC) -o 228.x 228.f

45_save.o: 45_save.f90
	$(XFC) -c 45_save.f90

358_result.x: 358_result.f90
	$(XFC) -o $@ $<

377.x: 377.f90
	$(XFC) -c -o 377.x $<; \
	[ ! -f 377.x ] && exit 1; \
	rm -rf __omni_tmp__; \
	$(XFC) -c $< --debug 1> /dev/null;\
	[ ! -d __omni_tmp__ ] && exit 1; \
        echo "PASS"

261.o: 261.f90
	$(XFC) -c $<

162.o: 162.f90
	$(XFC) -c $<

383.x: 383.f90
	$(XFC) -o $@ $<

392.x: 392.f90
	$(XFC) -I./392-include -o $@ $<

412.x: 412.f90
	$(XFC) -c $< ;\
	if [ ! -f m412.xmod ]; then exit 1; fi

run:
	$(XRUN) -np 2 ./module_test.x
	$(XRUN) -np 2 ./module_test0.x
	$(XRUN) -np 4 ./arg.x
	export XMP_NODE_SIZE0=2; \
	export XMP_NODE_SIZE1=2; \
	$(XRUN) -np 8 ./dnodes.x
	$(XRUN) -np 4 ./refobj.x
	$(XRUN) -np 2 ./103.x
	$(XRUN) -np 1 ./228.x
	$(XRUN) -np 1 ./358_result.x
	$(XRUN) -np 2 ./383.x
	$(XRUN) -np 1 ./392.x
	$(XRUN) -np 1 ./397.x
	$(XRUN) -np 1 ./278\ spacefile.x
#	$(XRUN) -np 4 ./save_desc.x

clean:
	rm -f *.x *.o *.*mod *.s
	rm -rf mod __omni_tmp__ 278\ module
