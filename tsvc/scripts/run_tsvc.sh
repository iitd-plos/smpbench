#!/bin/bash

# globals
ROOT=${HOME}
#ROOT=/home/thesis-code
BINARY_PATH_EQ=${ROOT}/superopt/build/etfg_i386/
BINARY_PATH_HARVEST=${ROOT}/superopt/build/i386_i386/
# BINARY_PATH="${ROOT}/superopt/build/"
export LD_LIBRARY_PATH=$ROOT/superopt/build/third_party/z3-z3-4.8.4/build
DEFAULT_EQ_PARAMS="--sage-query-timeout 200 --smt-query-timeout 200"
usage() {
	echo
	echo "Usage: $0 [-$] [-l] [-n] [-c COMPILER] [-o OPT_LVL] [-t TIMEOUT] [-d DBG_TOOL] [ -O LOG_FILE ] [ -D LOG_FILE_DIR ] [ -P EQ_PARAMS ] [BINARY_NAME:]FUNC_NAME"
	echo
	echo '            BINARY_NAME is assumed in case of ctests.'
	echo
	echo '           -$ disables .etfg and .tfg caching'
	echo '           -l disables logging'
	echo '           -n do not run eq, just generate .etfg and .tfg files'
	echo '           -C, COMPILER can be {gcc48, clang36, icc}. Default is: gcc48'
	echo '           -o, OPT_LVL can be {O2, O3}. Default is: O3'
	echo '           -t, TIMEOUT is time in seconds after which eq process will be sent SIGTERM.  Default: 3600 seconds'
	echo '           -d, DBG_TOOL can be {gdb, valgrind, rr, lldb}. Default is: None'
	echo '           -O, path of output .eqlog file. Default is: "LOG_FILE_DIR/FUNC_NAME.COMPILER.OPT_LVL.eqlog".'
	echo '               NOTE: -l takes precedence over it and it takes precendence over LOG_FILE_DIR'
	echo '           -P, params to be passed directly to eq cmd.  Default is: ${DEFAULT_EQ_PARAMS}'
	echo '           -D, dir of output .eqlog file. Default is: "eqlogs"'
  echo
	echo "E.g. : $0 -c gcc48 -o O2 show_move "
	echo
	exit 1
}

PROG_NAME=$0

# process arguments
while getopts ':$lnc:o:O:d:D:P:t:' opt; do
  case $opt in
    $)
      #echo "Disabling cache"
      NOCACHE=1
      ;;
    l)
      #echo "Disabling logging"
      NOLOGS=1
      ;;
    n)
      NOEQ=1
      ;;
    c)
      #echo "-c was triggered, Parameter: $OPTARG" >&2
      COMPILER=$OPTARG
      ;;
    o)
      #echo "-o was triggered, Parameter: $OPTARG" >&2
      OPT_LVL=$OPTARG
      ;;
    t)
      #echo "-o was triggered, Parameter: $OPTARG" >&2
      TIMEOUT=$OPTARG
      ;;
    O)
      #echo "-O was triggered, Paramter: $OPTARG" >&2
      LOG_FILE=$OPTARG
      ;;
    d)
      #echo "-d was triggered, Parameter: $OPTARG" >&2
      DBG_TOOL=$OPTARG
      ;;
    D)
      #echo "-D was triggered, Paramter: $OPTARG" >&2
      LOG_FILE_DIR=$OPTARG
      ;;
    P)
      #echo "-P was triggered, Paramter: $OPTARG" >&2
      EQ_PARAMS=$OPTARG
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      usage
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      usage
      ;;
  esac
done

# set defaults if arg not supplied
COMPILER=${COMPILER:-gcc48}
OPT_LVL=${OPT_LVL:-O3}
DBG_TOOL=${DBG_TOOL:-}
TIMEOUT=${TIMEOUT:-20000}
LOG_FILE_DIR=${LOG_FILE_DIR:-eqlogs}
EQ_PARAMS=${EQ_PARAMS:-${DEFAULT_EQ_PARAMS}}

# validate arguments
declare -a COMPILERS=("gcc48" "clang36" "icc")
if [[ ! -n ${COMPILERS[${COMPILER}]} ]]; then
    echo "Invalid compiler \"$COMPILER\""
    usage
fi

declare -a OPT_LVLS=("O2" "O3")
if [[ ! -n ${OPT_LVLS[${OPT_LVL}]} ]]; then
    echo "Invalid opt-level \"$OPT_LVL\""
    usage
fi

declare -a DBG_TOOLS=("time" "gdb" "lldb" "valgrind" "rr" "")
if [[ ! -n ${DBG_TOOLS[${DBG_TOOL}]} ]]; then
    echo "Invalid debug tool \"$DBG_TOOL\""
    usage
fi

# get function name
shift $((OPTIND-1))
if [ -z $1 ];
then
	echo "Error: function name missing!"
	usage
fi

temp=(${1//:/ }) # convert : to space and make it array
if [[ ${#temp[@]} -eq 2 ]];
then
  BINARY_NAME=${temp[0]}
  FUNC_NAME=${temp[1]}
else
  FUNC_NAME=$1
fi

mkdir -p ${ROOT}/{eqfiles,eqlogs}
#echo "${FUNC_NAME}"

if [[ ${PROG_NAME} == *"run_ctests.sh"* ]];
then
  TEST_PREFIX=ctests
  LLVM_SRC=$ROOT/smpbench-build/cint/ctests.bc.O0
  X86_SRC=$ROOT/smpbench-build/cint/ctests.${COMPILER}.${OPT_LVL}.i386
elif [[ ${PROG_NAME} == *"run_svcomp.sh"* ]];
then
  if [[ -v BINARY_NAME ]];
  then
    TEST_PREFIX=svcomp.${BINARY_NAME}
    LLVM_SRC=$ROOT/smpbench-build/svcomp/${BINARY_NAME}.bc.O0
    X86_SRC=$ROOT/smpbench-build/svcomp/${BINARY_NAME}.${COMPILER}.${OPT_LVL}.i386
  else
    echo "Error! BINARY_NAME is required for svcomp."
    usage
  fi
elif [[ ${PROG_NAME} == *"run_tsvc.sh"* ]];
then
  if [[ -v BINARY_NAME ]];
  then
    TEST_PREFIX=tsvc.${BINARY_NAME}
    LLVM_SRC=$ROOT/smpbench-build/tsvc/${BINARY_NAME}.bc.O0
    X86_SRC=$ROOT/smpbench-build/tsvc/${BINARY_NAME}.${COMPILER}.${OPT_LVL}.i386
  else
    echo "Error! BINARY_NAME is required for tsvc."
    usage
  fi
elif [[ ${PROG_NAME} == *"run_cprog.sh"* ]];
then
  if [[ -v BINARY_NAME ]];
  then
    TEST_PREFIX=cprog.${BINARY_NAME}
    LLVM_SRC=$ROOT/smpbench-build/cint/${BINARY_NAME}.bc.O0
    X86_SRC=$ROOT/smpbench-build/cint/${BINARY_NAME}.${COMPILER}.${OPT_LVL}.i386
  else
    echo "Error! BINARY_NAME is required for cprog."
    usage
  fi
elif [[ ${PROG_NAME} == *"run_spec2k.sh"* ]];
then
  if [[ -v BINARY_NAME ]];
  then
    TEST_PREFIX=spec2k.${BINARY_NAME}
    LLVM_SRC=$ROOT/spec2k/llvm-bc-O0/${BINARY_NAME}
    X86_SRC=$ROOT/spec2k/${COMPILER}-i386-${OPT_LVL}/${BINARY_NAME}
  else
    echo "Error! BINARY_NAME is required for spec2k."
    usage
  fi
else
  echo "Do not use run_eq.sh directly; use the links run_ctests.sh or run_spec2k.sh!"
  exit 2
fi

if [[ ! -v NOCACHE && -s $ROOT/eqfiles/${TEST_PREFIX}.etfg ]]; then
  ETFG_FILENAME=$ROOT/eqfiles/${TEST_PREFIX}.etfg
else
  ETFG_FILENAME=$ROOT/eqfiles/${TEST_PREFIX}.${FUNC_NAME}.etfg
fi
HARVEST_FILENAME=$ROOT/eqfiles/${TEST_PREFIX}.${FUNC_NAME}.${COMPILER}.${OPT_LVL}.harvest
TFG_FILENAME=$ROOT/eqfiles/${TEST_PREFIX}.${FUNC_NAME}.${COMPILER}.${OPT_LVL}.tfg
PROOF_FILE="${LOG_FILE_DIR}/${TEST_PREFIX}.${FUNC_NAME}.${COMPILER}.${OPT_LVL}.proof"
[[ -v NOLOGS ]] && LOG_FILE="/dev/null/" || LOG_FILE="${LOG_FILE:-${LOG_FILE_DIR}/${TEST_PREFIX}.${FUNC_NAME}.${COMPILER}.${OPT_LVL}.eqlog}"


# run llvm2tfg to construct etfg
if [[ -v NOCACHE || ! -s ${ETFG_FILENAME} ]]; then
  LLVM2TFG_CMD="$ROOT/llvm-build/bin/llvm2tfg -f ${FUNC_NAME} ${LLVM_SRC} -o ${ETFG_FILENAME} &&"
  #gdb --args $ROOT/llvm2tfg-build/bin/llvm2tfg -f ${FUNC_NAME} ${LLVM_SRC} -o ${ETFG_FILENAME}
fi

# harvest function
if [[ -v NOCACHE || ! -s ${HARVEST_FILENAME} ]]; then
  HARVEST_CMD="${BINARY_PATH_HARVEST}/harvest -functions_only -touch_callee_saves -live_callee_save -allow_unsupported -no_canonicalize_imms -no_eliminate_unreachable_bbls -function_name ${FUNC_NAME} -o ${HARVEST_FILENAME} -l "${HARVEST_FILENAME}.log" ${X86_SRC} &&"
  #gdb --args ${BINARY_PATH_HARVEST}/harvest -functions_only -touch_callee_saves -live_callee_save -allow_unsupported -no_canonicalize_imms -no_eliminate_unreachable_bbls -function_name ${FUNC_NAME} -o ${HARVEST_FILENAME} -l "${HARVEST_FILENAME}.log" ${X86_SRC}
fi

# generate tfg
if [[ -v NOCACHE || ! -s ${TFG_FILENAME} ]]; then
  EQGEN_CMD="${BINARY_PATH_EQ}/eqgen -f ${FUNC_NAME} -tfg_llvm ${ETFG_FILENAME} -l "${HARVEST_FILENAME}.log" -o ${TFG_FILENAME} -e ${X86_SRC} ${HARVEST_FILENAME} &&"
  #gdb --args ${BINARY_PATH_EQ}/eqgen -f ${FUNC_NAME} -tfg_llvm ${ETFG_FILENAME} -l "${HARVEST_FILENAME}.log" -o ${TFG_FILENAME} -e ${X86_SRC} ${HARVEST_FILENAME}
fi

# no eq
if [[ -v NOEQ ]]; then
    FINAL_CMD=${LLVM2TFG_CMD}${HARVEST_CMD}${EQGEN_CMD}true
    bash -c "${FINAL_CMD}" > ${LOG_FILE} 2>&1
    exit
fi

EQ_CMD="${BINARY_PATH_EQ}/eq ${EQ_PARAMS} --proof ${PROOF_FILE}  --f ${FUNC_NAME} ${ETFG_FILENAME} ${TFG_FILENAME}"

# run eq
case $DBG_TOOL in
  gdb)
    FINAL_CMD=${LLVM2TFG_CMD}${HARVEST_CMD}${EQGEN_CMD}true
    bash -c "${FINAL_CMD}"
    gdb --args $EQ_CMD
    ;;
  lldb)
    FINAL_CMD=${LLVM2TFG_CMD}${HARVEST_CMD}${EQGEN_CMD}true
    bash -c "${FINAL_CMD}"
    lldb -- $EQ_CMD
    ;;
  valgrind)
    FINAL_CMD=${LLVM2TFG_CMD}${HARVEST_CMD}${EQGEN_CMD}true
    bash -c "${FINAL_CMD}"
    valgrind -v --tool=memcheck --max-stackframe=4103256 $EQ_CMD
    ;;
  rr)
    FINAL_CMD=${LLVM2TFG_CMD}${HARVEST_CMD}${EQGEN_CMD}true
    bash -c "${FINAL_CMD}"
    rr record $EQ_CMD
    rr replay
    ;;
  time)
    FINAL_CMD=${LLVM2TFG_CMD}${HARVEST_CMD}${EQGEN_CMD}${EQ_CMD}
    time ${ROOT}/superopt/utils/chaperon.py "${FINAL_CMD}" --logfile ${LOG_FILE}
    ;;
  *)
    FINAL_CMD=${LLVM2TFG_CMD}${HARVEST_CMD}${EQGEN_CMD}" timeout --foreground ${TIMEOUT}s ${EQ_CMD}"
    ${ROOT}/superopt/utils/chaperon.py "${FINAL_CMD}" --logfile ${LOG_FILE}
    ;;
esac

