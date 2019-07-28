#!/bin/bash

ROOT=${HOME}
#ROOT=/home/thesis-code
LAST_LINK_NAME="last_result_cache"

usage() {
	echo
	echo "Usage: $0 [-O OPTIONS ] [-m MSG ] [ -c CORES ] BINARY_NAME EQ_FUNCS_FNAME"
	echo
	echo '           -O options to be passed to run_tsvc.sh'
	echo '           -m specify message to be put as header of result_cache file'
	echo '           -c, CORES # of parallel eq commands to be run'
  echo
	echo "E.g. : $0 -m 'test run' test_funcs"
	echo
	exit 1
}

# process arguments
while getopts ':m:O:c:' opt; do
  case $opt in
    m)
      echo "-m was triggered, Parameter: $OPTARG" >&2
      MSG=$OPTARG
      ;;
    O)
      echo "-O was triggered, Parameter: $OPTARG" >&2
      RUNCTESTS_OPTIONS=$OPTARG
      ;;
    c)
      echo "-c was triggered, Parameter: $OPTARG" >&2
      CORES=$OPTARG
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

CORES=${CORES:-2}

shift $((OPTIND-1))
if [ -z $1 ];
then
  usage
else
  INPUT_FNAME=$1
fi

COMMIT_ID=$(cat ${ROOT}/superopt/git-commit)
BUILD_BRANCH=$(readlink ${ROOT}/superopt/build)
RUN_ID="${BUILD_BRANCH}_$(date +"%F_%T")_${COMMIT_ID}"
OUTPUT_FNAME="${RUN_ID}_result_cache"
OUTPUT_DIRNAME="eqlogs_${RUN_ID}"

mkdir -p ${OUTPUT_DIRNAME}

echo "Input file name: $INPUT_FNAME"
echo "Output file name: $OUTPUT_FNAME"
echo "Output dir name: $OUTPUT_DIRNAME"
echo

> ${OUTPUT_FNAME}
if [[ ! -z ${RUNCTESTS_OPTIONS} ]]; then
  echo "# run_tsvc.sh options: ${RUNCTESTS_OPTIONS}" >> ${OUTPUT_FNAME}
fi
if [[ ! -z ${MSG} ]]; then
  echo "# ${MSG}" >> ${OUTPUT_FNAME}
fi
grep -v -e '^#' -e '^[ ]*$' "${INPUT_FNAME}" | time parallel -P${CORES} ./run_tsvc.sh -D ${OUTPUT_DIRNAME} ${RUNCTESTS_OPTIONS} {} | tee -a ${OUTPUT_FNAME}

# remove output file if empty
[ -f ${OUTPUT_FNAME} -a ! -s ${OUTPUT_FNAME} ] && rm ${OUTPUT_FNAME}

# create soft link for `last_result_cache'
ln -sf ${OUTPUT_FNAME} ${LAST_LINK_NAME}
