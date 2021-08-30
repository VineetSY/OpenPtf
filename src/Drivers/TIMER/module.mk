local_src := $(addprefix $(subdirectory)/,TIMER.c TIMER.h)
tim_dir := $(subdirectory)
# $(eval $(call make-library, $(subdirectory)/libdb.a, $(local_src)))
# .SECONDARY: $(call generated-source, $(local_src))
# $(subdirectory)/scanner.d: $(subdirectory)/playlist.d