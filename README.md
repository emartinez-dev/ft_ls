# ft_ls
For knowing the filesystem inside out, and how files and directories are sorted, I will code by myself one of the most used command: ls.

## Notes for myself

The original `ls` command sorts files and folders god knows how (yes I know,
depending on locale), which I find absurd sometimes.

In the subject page, it seems like the locale will be `LC_ALL=C`, but it sorts
the uppercase entries before the others, which I don't like.

This is my ls and I will make things the way want. I will follow this locale, but
the sorting will be made case insensitive.

Also, I implemented caching for syscalls like `getpwuid` and `getgrgid`, and twisted ft_printf so hard that the runtime for listing the whole root folder in 17 seconds (was 3:37 minutes before)

![image](https://github.com/user-attachments/assets/02bc7ff8-3f93-493b-8920-1ea46613a6e4)
