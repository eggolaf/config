call plug#begin('~/.vim/plugged')
  Plug 'xuhdev/vim-latex-live-preview', { 'for': 'tex' }
call plug#end()

filetype plugin on
filetype indent on

" theme
set background=dark
highlight clear
if exists("syntax_on")
    syntax reset
endif
let colors_name = "comments"

hi Normal ctermfg=LightGray ctermbg=Black
hi Comment    cterm=NONE ctermfg=DarkBlue
hi Constant   cterm=NONE ctermfg=LightGray
hi Identifier cterm=NONE ctermfg=LightGray
hi Function   cterm=NONE ctermfg=LightGray
hi Statement  cterm=NONE ctermfg=DarkGreen
hi PreProc    cterm=NONE ctermfg=LightGray
hi Type	      cterm=NONE ctermfg=DarkGreen
hi Special    cterm=NONE ctermfg=LightGray
hi Delimiter  cterm=NONE ctermfg=DarkGray
hi LineNr 	  cterm=None ctermfg=DarkYellow
hi CursorLineNr cterm=None ctermfg=DarkYellow
"hi NonText	  cterm=None ctermfg=Black
"hi Visual     ctermfg=White ctermbg=Black

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
