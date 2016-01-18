function ompf90_print_help()
{
cat <<EOF
usage: $1 <OPTIONS> <INPUTFILE> ...

Compile Driver Options

   -o <file>         : place the output into <file>.
   -I <dir>          : add the directory dir to the list of directories to be searched for header files.
   -J <dir>          : specify where to put .mod and .xmod files for compiled modules.
   -c                : compile and assemble, but do not link.
   -E                : preprocess only; do not compile, assemble or link.
   -cpp              : enable preprocess.
   -v,--verbose      : print processing status.
   --version         : print version.
   -h,--help         : print usage.
   --show-env        : show environment variables.
   --tmp             : output parallel code (__omni_tmp__<file>).
   --dry             : only print processing status (not compile).
   --debug           : save intermediate files in __omni_tmp__.
   --stop-pp         : save intermediate files and stop after preprocess.
   --stop-frontend   : save intermediate files and stop after frontend.
   --stop-translator : save intermediate files and stop after translator.
   --stop-backend    : save intermediate files and stop after backend.
   --stop-compile    : save intermediate files and stop after compile.

Process Options

  --Wp[option] : Add preprocessor option.
  --Wf[option] : Add frontend option.
  --Wx[option] : Add Xcode translator option.
  --Wb[option] : Add backend option.
  --Wn[option] : Add native compiler option.
  --Wl[option] : Add linker option.

Omni OpenACC Options

  -acc, --openacc : Enable OpenACC.
EOF
}

function ompf90_show_env()
{
    CONF_FILE=${OM_DRIVER_CONF_DIR}/ompf90.conf
    if [ -f $CONF_FILE ]; then
	for val in `sed '/^[[:space:]]*$/d' ${CONF_FILE} | grep -v '^#' | awk -F= '{print $1}'`
	do
	    echo -n ${val}=\"
            eval echo -n \"\$$val\"
	    echo \"
	done
    else
	omni_error_exit "$CONF_FILE not exist."
    fi
}

function get_target()
{
    ompf90 --show-env | grep TARGET | sed 's/TARGET=//' | sed "s/\"//g"
}

function ompf90_set_parameters()
{
    while [ -n "$1" ]; do
        case "$1" in
            *.f90|*.f|*.F90|*.F)
                f_files+=("$1");;
            *.a)
                archive_files+=("$1");;
            *.o)
                obj_files+=("$1");;
            -o)
                shift; output_file=("$1");;
            -J)
		shift;
		module_dir=("${1#-J}")
                module_opt=("-M${module_dir[0]}")
                target=`get_target`
                if [ "$target" = "Kcomputer-linux-gnu" -o "$target" = "FX10-linux-gnu" ]; then
                    other_args+=("${OMNI_MODINC}${module_dir}")
                else
                    other_args+=("${OMNI_MODINC}" "${module_dir}")
                fi;;
            -J?*)
                module_dir=("${1#-J}")
                module_opt=("-M${module_dir[0]}")
                target=`get_target`
                if [ "$target" = "Kcomputer-linux-gnu" -o "$target" = "FX10-linux-gnu" ]; then
                    other_args+=("${OMNI_MODINC}${module_dir}")
                else
                    other_args+=("${OMNI_MODINC}" "${module_dir}")
                fi;;
	    -I)
                shift;
		include_opt+=("-I$1")
		other_args+=("-I$1")
		module_dir=("${1#-I}")
                trans_module_opt+=("-M${module_dir[0]}");;
            -I?*)
		include_opt+=("$1")
		other_args+=("$1")
                module_dir=("${1#-I}")
                trans_module_opt+=("-M${module_dir[0]}");;
            -c)
		ENABLE_LINKER=false;;
	    -E)
		ONLY_PP=true;;
            -cpp)
                ENABLE_CPP=true;;
            -v|--verbose)
		VERBOSE=true;;
	    --version)
		omni_print_version; exit 0;;
            -h|--help)
		ompf90_print_help `basename $0`; exit 0;;
	    --show-env)
		ompf90_show_env; exit 0;;
            --tmp)
		OUTPUT_TEMPORAL=true;;
            --dry)
		DRY_RUN=true;;
	    --debug)
		ENABLE_DEBUG=true;;
            --stop-pp)
		VERBOSE=true; STOP_PP=true;;
            --stop-frontend)
		VERBOSE=true; STOP_FRONTEND=true;;
	    --stop-translator)
		VERBOSE=true; STOP_TRANSLATOR=true;;
	    --stop-backend)
		VERBOSE=true; STOP_BACKEND=true;;
	    --stop-compile)
		VERBOSE=true; STOP_COMPILE=true;;
            --Wp*)
                pp_add_opt+=("${1#--Wp}");;
            --Wf*)
                frontend_add_opt+=("${1#--Wf}");;
            --Wx*)
                xcode_translator_add_opt+=("${1#--Wx}");;
            --Wn*)
                native_add_opt+=("${1#--Wn}");;
            --Wb*)
                backend_add_opt+=("${1#--Wb}");;
            --Wl*)
                linker_add_opt+=("${1#--Wl}");;
            --openmp|-omp)
                ENABLE_OPENMP=true;;
	    -acc|--openacc)
		omni_error_exit "OpenACC for ompf90 has been not implemented yet."
		if [ ${ENABLE_ACC} = "0" ]; then
		    omni_error_exit "warning: $arg option is unavailable, rebuild the compiler with ./configure --enable-openacc"
		fi
		ENABLE_ACC=true
		;;
            *)
                other_args+=("$1");;
	esac
	shift
    done

    if test $OUTPUT_TEMPORAL = true -a $DRY_RUN = true; then
        omni_error_exit "cannot use both --tmp and --dry options at the same time."
    fi
}