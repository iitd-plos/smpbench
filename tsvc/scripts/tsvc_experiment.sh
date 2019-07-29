#!/bin/bash

CORES=15

./parallel-tsvc.sh -c $CORES -O' -$ -o "O3" -c "gcc48"   -P" --unroll-factor 7  --global-timeout 30000 --smt-query-timeout 300 --initial_lookahead 6 "' eq_funcs_tsvc
./parallel-tsvc.sh -c $CORES -O' -$ -o "O3" -c "icc"     -P" --unroll-factor 7  --global-timeout 30000 --smt-query-timeout 300 --initial_lookahead 6 "' eq_funcs_tsvc
./parallel-tsvc.sh -c $CORES -O' -$ -o "O3" -c "clang36" -P" --unroll-factor 15 --global-timeout 50000 --smt-query-timeout 300 --initial_lookahead 6 "' eq_funcs_tsvc


