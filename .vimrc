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

hi Normal ctermfg=White ctermbg=Yellow
hi Comment    cterm=NONE ctermfg=DarkCyan
hi Constant   cterm=NONE ctermfg=White
hi Identifier cterm=NONE ctermfg=White
hi Function   cterm=NONE ctermfg=White
hi Statement  cterm=NONE ctermfg=White
hi PreProc    cterm=NONE ctermfg=White
hi Type	      cterm=NONE ctermfg=White
hi Special    cterm=NONE ctermfg=White
hi Delimiter  cterm=NONE ctermfg=White
hi LineNr 	  cterm=None ctermfg=DarkCyan
hi CursorLineNr cterm=None ctermfg=DarkCyan
hi NonText	  cterm=None ctermfg=White
" hi Visual     ctermfg=None ctermbg=Yellow

:highlight ExtraWhitespace ctermbg=Yellow
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
