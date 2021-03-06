include config-host.mak
include Make.conf

all:: $(build) $(build)/Makefile
	make -C $(build)

.PHONY: cint superopt_test harvest_all svcomp tsvc
$(MAKE_TARGETS) crosstool compcert lmem_run cint tsvc cint-msp430 superopt_test harvest_all svcomp:: $(build) $(build)/Makefile
	make -C $(build) $@

$(build):
	mkdir -p $@

$(build)/Makefile: Makefile.build Makefile.cint Makefile.compcert Makefile.crosstool Makefile.svcomp Make.conf Makefile.tsvc Makefile.tsvcnonvec
	cp $< $@

tar:: cleansrc
	cd .. && \
		tar cjf bak/$(NAME)-`date +%d`-`date +%m`-`date +%y`-`date +%H`.tbz2 $(NAME)
	ctags -R 2>/dev/null

bak: tar
	scp ../bak/$(NAME)-`date +%d`-`date +%m`-`date +%y`-`date +%H`.tbz2 sbansal@sri.cse.iitd.ernet.in:bak/

cscope::
	ls */*.[ch] > cscope.files

tags::
	find "$(SRCDIR)" -name '*.[hc]' -print0 | xargs -0 etags

clean: $(build) $(build)/Makefile cleansrc
	make -C $(build) clean

cleansrc::
	CSCOPE_OUTS="`find . -name cscope.out`";				\
	TAGS="`find . -name tags`";											\
	for d in $$CSCOPE_OUTS $$TAGS; do								\
	  rm -rf "$$d";														  		\
	done;

distclean: clean
	rm -rf $(build) config-host.mak config-host.h misc/config_host.pm

bzip2_run:: input.combined
	time $(build)/cint/bzip2.clang.eqchecker.O3.i386
