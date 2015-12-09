include config-host.mak
include Make.conf

all:: $(build) $(build)/Makefile
	make -C $(build)

$(MAKE_TARGETS) lmem_run: $(build) $(build)/Makefile
	make -C $(build) $@

$(build):
	mkdir -p $@

$(build)/Makefile: Makefile.build
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
