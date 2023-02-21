UNAME := $(shell uname)

installOSspecific:
ifeq ($(UNAME), Linux)
   	$(shell mkdir -p ./build)
   	$(shell cp installLinux.sh ./build && cd ./build && chmod +x installLinux.sh && ./installLinux.sh)
endif
ifeq ($(UNAME), Darwin)
   	$(shell mkdir -p ./build)
   	$(shell cp installMac.sh ./build && cd ./build && chmod +x installMac.sh && ./installMac.sh)
endif

install:
ifeq ($(wildcard ./build), )
	$(MAKE) installOSspecific
endif

run: install
	cmake .

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
	$(RM) $(OBJS)

.PHONY: all clean fclean re
