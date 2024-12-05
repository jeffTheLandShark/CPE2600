\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{assignment}[Format class for word processed assignments]

\RequirePackage[table,xcdraw]{xcolor}

\LoadClass[12pt]{article}

\RequirePackage[letterpaper,margin=1in,tmargin=0.5in,includeheadfoot]{geometry}
\RequirePackage{fancyhdr}
\RequirePackage{titlesec}
\RequirePackage[utf8]{inputenc}
\RequirePackage{fourier}
\RequirePackage{graphicx}
\RequirePackage{float}
\RequirePackage{pdfpages}
\RequirePackage[labelfont=bf]{caption}
\RequirePackage{multirow}
\RequirePackage[colorlinks=true,linkcolor=blue, filecolor=magenta, urlcolor=blue]{hyperref}
\RequirePackage{enumitem}

\RequirePackage{booktabs}
\RequirePackage{multicol}
\RequirePackage{blindtext}
\RequirePackage{amsmath}
\RequirePackage{amsfonts}
\RequirePackage{mathtools}

\RequirePackage{calc}
\RequirePackage{hyperref}
\RequirePackage{ifpdf}
\RequirePackage{attachfile}

\setkeys{Gin}{width=\textwidth}
\setlist{itemsep=0.2em, topsep=0.2em, parsep=0pt, partopsep=0pt}


\titleformat{\section}{\bfseries\fontsize{16pt}{12}\selectfont}{}{0em}{}
\titlespacing\section{0pt}{12pt plus 4pt minus 2pt}{0pt plus 2pt minus 2pt}

\setlength\parskip{1em plus 0.1em minus 0.2em}

\makeatletter
\renewcommand*{\fps@figure}{H}
\renewcommand*{\fps@table}{H}

\g@addto@macro\@floatboxreset\centering

\newcommand{\qa}[3]
{
\begin{enumerate}[left=7pt]
    \item[#1.] #2
    \begin{enumerate}[label=\textit{Ans.}]
        \item #3
    \end{enumerate}
\end{enumerate}
}
\newcommand{\qano}[2]
{
\begin{enumerate}[left=7pt]
    \item[#1.]
    \begin{itemize}[label=\textit{Ans.}]
        \item #2
    \end{itemize}
\end{enumerate}
}
\newcommand{\submissionDate}[1]{\def\submissionDate{#1}}
\newcommand{\prof}[1]{\def\prof{#1}}
\newcommand{\className}[1]{\def\className{#1}}
\newcommand{\classCode}[1]{\def\classCode{#1}}
\newcommand{\assignment}[1]{\def\assignment{#1}}

\DeclareListParser{\ListParser}{;}
\newcommand{\learningTarget}[1]{\def\learningTarget{#1}}
\newcommand{\lt}[1]{
    \section{Learning Targets}
    \begin{itemize}[itemsep=0pt]
        \renewcommand{\do}[1]{\item ##1}
          \expandafter\expandafter\expandafter\ListParser\expandafter\expandafter\expandafter{#1}
    \end{itemize}
}

\fancypagestyle{firststyle}
{
    \fancyhf{}
    
    \lhead{
        \Large{
           \\ \submissionDate{}\\
             \@author \\
             \classCode - \className
        }
    }
    
    \rhead{
        \includegraphics[height=36pt, width=29pt]{msoe.png}\\
        \Large{
            \prof 
        }
    }
    \cfoot{1}
    \newgeometry{margin=1in,tmargin=.5in,headsep=1.25in,includehead}
    
}

\renewcommand\maketitle{
{
\thispagestyle{firststyle}
\begin{center}
    \LARGE{\@title}
\end{center}
}
}
\makeatother