CC            = @MPI_CC@
TLOG_INC_DIR  = $(top_builddir)/libtlog/src_mpi
lib_LIBRARIES = libxmp.a
CFLAGS        = @MPI_CFLAGS@ -I../include -I$(TLOG_INC_DIR)
LDFLAGS       = @MPI_CLIBS@

libxmp_a_SOURCES = ../include/xmp_internal.h ../include/xmp_constant.h ../include/xmp_data_struct.h \
                   ../include/xmp_math_function.h xmp_lib.c xmp_util.c xmp_world.c xmp_nodes_stack.c \
                   xmp_nodes.c xmp_template.c xmp_barrier.c xmp_reduce.c xmp_bcast.c \
                   xmp_align.c xmp_shadow.c xmp_array_section.c xmp_loop.c xmp_gmove.c \
                   xmp_math_function.c xmp_runtime.c xmp_tlog_runtime.c xmp_io.c xmp_reflect.c xmp_pack_vector.c \
		   xmp_intrinsic.c xmp_section_desc.c xmp_sort.c xmp_async.c

if GASNET
    libxmp_a_SOURCES += xmp_onesided.c xmp_onesided_gasnet.c xmp_coarray.c xmp_coarray_utils.c xmp_coarray_local.c \
			xmp_coarray_local_utils.c xmp_post_wait.c xmp_post_wait_gasnet.c \
	                xmp_coarray_gasnet.c xmp_coarray_gasnet_utils.c xmp_lock_unlock.c xmp_lock_unlock_gasnet.c \
			xmp_intrinsic_gasnet.c
    CFLAGS           += -D_XMP_GASNET
else
if MPI3_ONESIDED
#xmp_coarray_mpi_util.c xmp_lock_unlock.c xmp_lock_unlock_mpi.c
    libxmp_a_SOURCES += xmp_onesided.c xmp_onesided_mpi.c xmp_coarray.c xmp_coarray_utils.c xmp_coarray_local.c \
			xmp_coarray_local_utils.c xmp_post_wait.c xmp_post_wait_mpi.c \
	                xmp_coarray_mpi.c xmp_intrinsic_mpi.c
endif	
endif

if FJRDMA
    libxmp_a_SOURCES += xmp_onesided.c xmp_onesided_fjrdma.c xmp_coarray.c xmp_coarray_utils.c xmp_coarray_local.c \
			xmp_coarray_local_utils.c xmp_post_wait.c xmp_post_wait_fjrdma.c \
	                xmp_coarray_fjrdma.c xmp_coarray_fjrdma_utils.c xmp_intrinsic_fjrdma.c
    CFLAGS           += -D_XMP_FJRDMA
endif

if MPI3
    CFLAGS += -D_XMP_MPI3
endif

if MPI3_ONESIDED
    CFLAGS += -D_XMP_MPI3_ONESIDED
endif

if LIBBLAS
    CFLAGS += -D_XMP_LIBBLAS
endif

if SSL2BLAMP
    CFLAGS += -D_XMP_SSL2BLAMP
endif

if INTELMKL
    CFLAGS += -D_XMP_INTELMKL
endif

if TCA
#  xmp_coarray_gasnet_utils.c xmp_lock_unlock_gasnet.c xmp_lock_unlock.c
    libxmp_a_SOURCES += xmp_onesided.c xmp_onesided_tca.c xmp_coarray.c xmp_coarray_utils.c xmp_coarray_local.c \
			xmp_coarray_local_utils.c xmp_post_wait.c xmp_post_wait_tca.c \
	                xmp_coarray_tca.c 
    libxmp_a_SOURCES += xmp_reflect_tca.c
    CFLAGS        += -D_XMP_TCA
endif

if XACC
    libxmp_a_SOURCES += xmp_reflect_acc.c xmp_reduce_acc.c xmp_bcast_acc.c xmp_reflect_gpu.c xmp_reduce_gpu.c xmp_gpu_pack.cu xmp_gmove_acc.c xmp_coarray_acc.c
    CFLAGS           += -D_XMP_XACC -I@CUDA_PREFIX@/include
    GPUCC             = @GPU_CMD@
    GPUCFLAGS         = @GPU_CFLAGS@

.cu.o:
	$(GPUCC) $(GPUCFLAGS) -I../include -c $@ $<
endif

clean-local:
	rm -f *~ *.core core core.*
