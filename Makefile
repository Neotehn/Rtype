

install:
    ifeq ($(wildcard ./build),)
        # If directory does not exist, create it
        $(shell mkdir -p ./build)
        $(shell cp install.sh ./build && cd ./build && chmod +x install.sh && ./install.sh)
    endif


clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
	$(RM) $(OBJS)

.PHONY: all clean fclean re