# ft_ls
For knowing the filesystem inside out, and how files and directories are sorted, I will code by myself one of the most used command: ls.

## Notes for myself

The original `ls` command sorts files and folders god knows how (yes I know,
depending on locale), which I find absurd sometimes.

In the subject page, it seems like the locale will be `LC_ALL=C`, but it sorts
the uppercase entries before the others, which I don't like.

This is my ls and I will make things the way want. I will follow this locale, but
the sorting will be made case insensitive.