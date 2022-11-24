FROM ubuntu:16.04

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install g++ valgrind -y
RUN apt-get install libreadline6 libreadline6-dev -y
RUN apt-get update && apt-get install make

# FROM 		archlinux:latest
# ENTRYPOINT	[ "/bin/zsh" ]

# ARG			USER $USER
# ENV			USER $USER
# RUN			useradd -ms /bin/zsh -rg root $USER

# RUN			pacman -Syu  --noconfirm \
# 			base-devel \
# 			gcc \
# 			make \
# 			readline \
# 			valgrind \
# 			man-db \
# 			man-pages \
# 			nano \
# 			curl \
# 			git \
# 			lsof \
# 			lldb \
# 			zsh \
# 			diffutils \
# 			moreutils \
# 			python3

# RUN			chsh -s /bin/zsh

# RUN			source "/etc/profile.d/debuginfod.sh"

# RUN			python -m ensurepip --upgrade && \
# 			python3 -m pip install --upgrade pip setuptools && \
# 			python3 -m pip install norminette

# RUN			sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# RUN			echo 'PROMPT="Arch %(?:%{%}➜ :%{%}➜ ) %{$fg[cyan]%}%c%{$reset_color%} $(git_prompt_info)"' >> ~/.zshrc && \
# 			echo 'export P_DIR="~/Users/$USER/Desktop/Projects/minishell"' >> ~/.zshrc && \
# 			echo 'export P_EXEC="./minishell"' >> ~/.zshrc && \
# 			echo 'alias mm="make && $P_EXEC"' >> ~/.zshrc && \
# 			echo 'alias vg="make && valgrind -q --leak-check=full $P_EXEC"' >> ~/.zshrc && \
# 			echo 'cd "$P_DIR" >> ~/.zshrc' >> ~/.zshrc
