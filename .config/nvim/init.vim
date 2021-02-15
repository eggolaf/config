call plug#begin('~/.vim/plugged')
  Plug 'xuhdev/vim-latex-live-preview', { 'for': 'tex' }
  Plug 'dracula/vim', { 'as': 'dracula' }
  Plug 'morhetz/gruvbox'
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
hi Normal ctermfg=Black ctermbg=White guifg=Black guibg=White
hi Comment    cterm=NONE ctermfg=DarkGreen
hi Constant   cterm=NONE ctermfg=Black
hi Identifier cterm=NONE ctermfg=Black
hi Function   cterm=NONE ctermfg=Black
hi Statement  cterm=NONE ctermfg=Black
hi PreProc    cterm=NONE ctermfg=Black
hi Type	      cterm=NONE ctermfg=Black
hi Special    cterm=NONE ctermfg=Black
hi Delimiter  cterm=NONE ctermfg=Black
hi LineNr 	  cterm=None ctermfg=Black
hi CursorLineNr cterm=None ctermfg=Black

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
set shiftwidth=0
set smarttab
set copyindent
set scrolloff=3

let g:tex_flavor='latex'
let g:livepreview_engine = 'xelatex'
let g:livepreview_previewer = 'zathura'
let Tex_FoldedSections=""
let Tex_FoldedEnvironments=""
let Tex_FoldedMisc=""
