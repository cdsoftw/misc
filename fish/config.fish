if status is-interactive
    # Commands to run in interactive sessions can go here
    starship init fish | source
    load_nvm > /dev/stderr

    # name: CoffeeAndCode
    # Theme colors
    set fish_color_normal 5f5f5f
    set fish_color_command 5f87ff
    set fish_color_quote brown
    set fish_color_redirection normal
    set fish_color_end bcbcbc
    set fish_color_error red --bold
    set fish_color_param 5f87ff
    set fish_color_comment red
    set fish_color_match cyan
    set fish_color_search_match --background=purple
    set fish_color_operator cyan
    set fish_color_escape cyan
    set fish_color_cwd 00875f
    set fish_pager_color_prefix cyan
    set fish_pager_color_completion normal
    set fish_pager_color_description 555 yellow
    set fish_pager_color_progress cyan
    set fish_pager_color_secondary

    set fish_color_host cyan
    set fish_color_user cyan
end

