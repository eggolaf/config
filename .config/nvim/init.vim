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
hi Normal ctermfg=White ctermbg=Black guifg=White guibg=Black
hi Comment    cterm=NONE ctermfg=Green
hi Constant   cterm=NONE ctermfg=White
hi Identifier cterm=NONE ctermfg=White
hi Function   cterm=NONE ctermfg=White
hi Statement  cterm=NONE ctermfg=White
hi PreProc    cterm=NONE ctermfg=White
hi Type	      cterm=NONE ctermfg=White
hi Special    cterm=NONE ctermfg=White
hi Delimiter  cterm=NONE ctermfg=White

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
