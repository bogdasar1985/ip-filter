cat ip_filter.tsv | ./ip_filter > result.tsv
diff result.tsv ip_filter.tst