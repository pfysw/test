
#SRC = ${wildcard *.c}
#OBJ = ${patsubst %.c, %.o, ${SRC}}
INC = -I.. -I../../ext/rbu
TEMP_STORE = -DSQLITE_TEMP_STORE=1

OBJ = amatch.o \
carray.o \
closure.o \
csv.o \
eval.o \
explain.o \
fileio.o \
fts3_term.o \
fts3_test.o \
fts5_tcl.o \
fts5_test_mi.o \
fts5_test_tok.o \
fuzzer.o \
ieee754.o \
mmapwarm.o \
nextchar.o \
normalize.o \
percentile.o \
prefixes.o \
regexp.o \
remember.o \
series.o \
spellfix.o \
sqlite3async.o \
sqlite3expert.o \
tclsqlite.o \
test1.o \
test2.o \
test3.o \
test4.o \
test5.o \
test6.o \
test7.o \
test8.o \
test9.o \
test_async.o \
test_autoext.o \
test_backup.o \
test_bestindex.o \
test_blob.o \
test_btree.o \
test_config.o \
test_delete.o \
test_demovfs.o \
test_devsym.o \
test_expert.o \
test_fs.o \
test_func.o \
test_hexio.o \
test_init.o \
test_intarray.o \
test_journal.o \
test_malloc.o \
test_md5.o \
test_multiplex.o \
test_mutex.o \
test_onefile.o \
test_osinst.o \
test_pcache.o \
test_quota.o \
test_rbu.o \
test_rtree.o \
test_schema.o \
test_server.o \
test_session.o \
test_superlock.o \
test_syscall.o \
test_tclsh.o \
test_tclvar.o \
test_thread.o \
test_vdbecov.o \
test_vfs.o \
test_windirent.o \
test_window.o \
test_wsd.o \
totype.o \
unionvtab.o \
wholenumber.o \
zipfile.o

TCC += $(INC) -DSQLITE_NO_SYNC=1 $(TEMP_STORE) $(TESTFIXTURE_FLAGS)
#TCC += $(INC) -DSQLITE_NO_SYNC=1 $(TEMP_STORE)
.PHONY:bb
#bb:test_autoext.o
bb:libtest.a
	
#@echo $(TESTFIXTURE_FLAGS)
	echo end
libtest.a:$(OBJ)
	ar -rc libtest.a $(OBJ)
	
		
#test1.o:$(TOP)/src/test1.c
#	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
amatch.o:$(TOP)/ext/misc/amatch.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
carray.o:$(TOP)/ext/misc/carray.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
closure.o:$(TOP)/ext/misc/closure.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
csv.o:$(TOP)/ext/misc/csv.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
eval.o:$(TOP)/ext/misc/eval.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
explain.o:$(TOP)/ext/misc/explain.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
fileio.o:$(TOP)/ext/misc/fileio.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
fts3_term.o:$(TOP)/ext/fts3/fts3_term.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
fts3_test.o:$(TOP)/ext/fts3/fts3_test.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
fts5_tcl.o:$(TOP)/ext/fts5/fts5_tcl.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
fts5_test_mi.o:$(TOP)/ext/fts5/fts5_test_mi.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
fts5_test_tok.o:$(TOP)/ext/fts5/fts5_test_tok.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
fuzzer.o:$(TOP)/ext/misc/fuzzer.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
ieee754.o:$(TOP)/ext/misc/ieee754.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
mmapwarm.o:$(TOP)/ext/misc/mmapwarm.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
nextchar.o:$(TOP)/ext/misc/nextchar.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
normalize.o:$(TOP)/ext/misc/normalize.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
percentile.o:$(TOP)/ext/misc/percentile.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
prefixes.o:$(TOP)/ext/misc/prefixes.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
regexp.o:$(TOP)/ext/misc/regexp.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
remember.o:$(TOP)/ext/misc/remember.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
series.o:$(TOP)/ext/misc/series.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
spellfix.o:$(TOP)/ext/misc/spellfix.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
sqlite3async.o:$(TOP)/ext/async/sqlite3async.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
sqlite3expert.o:$(TOP)/ext/expert/sqlite3expert.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
tclsqlite.o:$(TOP)/src/tclsqlite.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test1.o:$(TOP)/src/test1.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test2.o:$(TOP)/src/test2.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test3.o:$(TOP)/src/test3.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test4.o:$(TOP)/src/test4.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test5.o:$(TOP)/src/test5.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test6.o:$(TOP)/src/test6.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test7.o:$(TOP)/src/test7.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test8.o:$(TOP)/src/test8.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test9.o:$(TOP)/src/test9.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_async.o:$(TOP)/src/test_async.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_autoext.o:$(TOP)/src/test_autoext.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_backup.o:$(TOP)/src/test_backup.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_bestindex.o:$(TOP)/src/test_bestindex.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_blob.o:$(TOP)/src/test_blob.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_btree.o:$(TOP)/src/test_btree.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_config.o:$(TOP)/src/test_config.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_delete.o:$(TOP)/src/test_delete.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_demovfs.o:$(TOP)/src/test_demovfs.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_devsym.o:$(TOP)/src/test_devsym.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_expert.o:$(TOP)/ext/expert/test_expert.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_fs.o:$(TOP)/src/test_fs.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_func.o:$(TOP)/src/test_func.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_hexio.o:$(TOP)/src/test_hexio.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_init.o:$(TOP)/src/test_init.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_intarray.o:$(TOP)/src/test_intarray.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_journal.o:$(TOP)/src/test_journal.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_malloc.o:$(TOP)/src/test_malloc.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_md5.o:$(TOP)/src/test_md5.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_multiplex.o:$(TOP)/src/test_multiplex.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_mutex.o:$(TOP)/src/test_mutex.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_onefile.o:$(TOP)/src/test_onefile.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_osinst.o:$(TOP)/src/test_osinst.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_pcache.o:$(TOP)/src/test_pcache.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_quota.o:$(TOP)/src/test_quota.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_rbu.o:$(TOP)/ext/rbu/test_rbu.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_rtree.o:$(TOP)/src/test_rtree.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_schema.o:$(TOP)/src/test_schema.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_server.o:$(TOP)/src/test_server.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_session.o:$(TOP)/ext/session/test_session.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_superlock.o:$(TOP)/src/test_superlock.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_syscall.o:$(TOP)/src/test_syscall.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_tclsh.o:$(TOP)/src/test_tclsh.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_tclvar.o:$(TOP)/src/test_tclvar.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_thread.o:$(TOP)/src/test_thread.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_vdbecov.o:$(TOP)/src/test_vdbecov.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_vfs.o:$(TOP)/src/test_vfs.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_windirent.o:$(TOP)/src/test_windirent.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_window.o:$(TOP)/src/test_window.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
test_wsd.o:$(TOP)/src/test_wsd.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
totype.o:$(TOP)/ext/misc/totype.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
unionvtab.o:$(TOP)/ext/misc/unionvtab.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
wholenumber.o:$(TOP)/ext/misc/wholenumber.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
zipfile.o:$(TOP)/ext/misc/zipfile.c
	$(TCC)  -c $< -o $@ $(LIBTCL) $(TLIBS)
	
clean:
	rm -f *.o
	rm -f libtest.a