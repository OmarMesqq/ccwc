#!/bin/bash
set -uo pipefail

make release

echo "Step 1 (-c option): number of bytes"
WC_CMD_1=$(wc -c test.txt)
CCWC_CMD_1=$(./ccwc -c test.txt)

WC_CMD_2=$(wc -c utf8_peq.txt)
CCWC_CMD_2=$(./ccwc -c utf8_peq.txt)

echo "Comparing test.txt"
printf '%s' "$WC_CMD_1"
echo ""
printf '%s' "$CCWC_CMD_1"
echo ""

cmp -s <(printf '%s' "$WC_CMD_1") <(printf '%s' "$CCWC_CMD_1")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for test.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Comparing utf8_peq.txt"
printf '%s' "$WC_CMD_2"
echo ""
printf '%s' "$CCWC_CMD_2"
echo ""

cmp -s <(printf '%s' "$WC_CMD_2") <(printf '%s' "$CCWC_CMD_2")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for utf8_peq.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac


echo "Step 2 (-l option): number of lines"
WC_CMD_1=$(wc -l test.txt)
CCWC_CMD_1=$(./ccwc -l test.txt)

WC_CMD_2=$(wc -l utf8_peq.txt)
CCWC_CMD_2=$(./ccwc -l utf8_peq.txt)

echo "Comparing test.txt"
printf '%s' "$WC_CMD_1"
echo ""
printf '%s' "$CCWC_CMD_1"
echo ""

cmp -s <(printf '%s' "$WC_CMD_1") <(printf '%s' "$CCWC_CMD_1")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for test.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Comparing utf8_peq.txt"
printf '%s' "$WC_CMD_2"
echo ""
printf '%s' "$CCWC_CMD_2"
echo ""

cmp -s <(printf '%s' "$WC_CMD_2") <(printf '%s' "$CCWC_CMD_2")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for utf8_peq.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac


echo "Step 3 (-w option): number of words"
WC_CMD_1=$(wc -w test.txt)
CCWC_CMD_1=$(./ccwc -w test.txt)

WC_CMD_2=$(wc -w utf8_peq.txt)
CCWC_CMD_2=$(./ccwc -w utf8_peq.txt)

echo "Comparing test.txt"
printf '%s' "$WC_CMD_1"
echo ""
printf '%s' "$CCWC_CMD_1"
echo ""

cmp -s <(printf '%s' "$WC_CMD_1") <(printf '%s' "$CCWC_CMD_1")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for test.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Comparing utf8_peq.txt"
printf '%s' "$WC_CMD_2"
echo ""
printf '%s' "$CCWC_CMD_2"
echo ""

cmp -s <(printf '%s' "$WC_CMD_2") <(printf '%s' "$CCWC_CMD_2")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for utf8_peq.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Step 4 (-m option): number of characters"
WC_CMD_1=$(wc -m test.txt)
CCWC_CMD_1=$(./ccwc -m test.txt)

WC_CMD_2=$(wc -m utf8_peq.txt)
CCWC_CMD_2=$(./ccwc -m utf8_peq.txt)

echo "Comparing test.txt"
printf '%s' "$WC_CMD_1"
echo ""
printf '%s' "$CCWC_CMD_1"
echo ""

cmp -s <(printf '%s' "$WC_CMD_1") <(printf '%s' "$CCWC_CMD_1")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for test.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "Comparing utf8_peq.txt"
printf '%s' "$WC_CMD_2"
echo ""
printf '%s' "$CCWC_CMD_2"
echo ""

cmp -s <(printf '%s' "$WC_CMD_2") <(printf '%s' "$CCWC_CMD_2")
case $? in
 0) ;;
 1) echo "TEST FAILED! output mismatch for utf8_peq.txt"; exit 1 ;;
 *) echo "ERROR when comparing outputs"; exit 1 ;;
esac

echo "SUCCESS! All tests passed."
