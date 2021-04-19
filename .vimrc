call plug#begin('~/.vim/plugged')
  Plug 'xuhdev/vim-latex-live-preview', { 'for': 'tex' }
  Plug 'octol/vim-cpp-enhanced-highlight'
call plug#end()

filetype plugin on
filetype indent on

" theme
set background=dark
highlight clear
if exists("syntax_on")
    syntax reset
endif

let colors_name = "eggolaf"
hi Normal ctermfg=DarkRed ctermbg=Black
hi Comment    cterm=NONE ctermfg=DarkGreen
hi Constant   cterm=NONE ctermfg=DarkCyan
hi Statement  cterm=NONE ctermfg=DarkMagenta
hi PreProc    cterm=NONE ctermfg=DarkBlue
hi Type	      cterm=NONE ctermfg=DarkBlue
hi Special    cterm=NONE ctermfg=DarkCyan
hi Delimiter  cterm=NONE ctermfg=DarkBlue
hi LineNr 	  cterm=None ctermfg=DarkRed
hi CursorLineNr cterm=None ctermfg=DarkRed
hi NonText	  cterm=None ctermfg=Black
hi Identifier cterm=NONE ctermfg=DarkYellow
hi Function   cterm=NONE ctermfg=DarkMagenta
"hi Visual     ctermfg=None ctermbg=Black

:highlight ExtraWhitespace ctermbg=Black
:match ExtraWhitespace /\s\+$/

" draw tabs and highlight them specially
"set list
"set listchars=tab:>-
":hi Tabs cterm=None ctermfg=DarkBlue
":match Tabs /\t/

set nu
set rnu
set wildignore=*.o
set wildmenu
set incsearch
set nohlsearch
set ruler
set lazyredraw
set hidden
set tabstop=4
set shiftwidth=4
set smarttab
set copyindent
set scrolloff=3

set encoding=utf-8

let g:tex_flavor='latex'
let g:livepreview_engine = 'xelatex'
let g:livepreview_previewer = 'zathura'
let Tex_FoldedSections=""
let Tex_FoldedEnvironments=""
let Tex_FoldedMisc=""

let g:cpp_class_decl_highlight = 1
let g:cpp_class_scope_highlight = 1
