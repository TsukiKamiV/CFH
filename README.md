# How to fix Francinette's installation script for bash env

- once installation script finished execution, you shall see $venv> prompt, exit.
- $ cat ~/.zsh
- you should see two lines at the bottom, start with 'alias', copy these two lines.
- $ vim ~/.bash_profile
- paste two lines to the bottom
- This step is optional but recommended: The original lines should be written like this: alias paco=bla bla bla, let's change it to alias paco="bla bla bla" (add quotes on the right side of the '=')
- :wq (exit vim)
- $ source ~/.bash_profile
- DONE
