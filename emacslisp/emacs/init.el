;;start package.el with emacs
(require 'package)
;;add MELPA to repository list
(add-to-list 'package-archives
			 '("melpa" . "http://melpa.org/packages/"))
(when (< emacs-major-version 24)
  ;; For important compatibility libraries like cl-lib
  (add-to-list 'package-archives '("gnu" . "http://elpa.gnu.org/packages/")))
;;initialize package.el
(package-initialize)

;;start auto-complete with emacs
(require 'auto-complete)
;;do default config for auto-complete
(require 'auto-complete-config)
(ac-config-default)

;;needed if you install yasnippet from github
;;not needed if you install from package
(add-to-list 'load-path
              "~/.emacs.d/elisp/yasnippet")
;;start yasnippet with emacs
(require 'yasnippet)
(yas-global-mode 1)

;;let's define a function which initializes auto-complete-c-headers and gets called for c/c++ hooks
(defun my:ac-c-headers-init()
  (require 'auto-complete-c-headers)
  (add-to-list 'ac-sources 'ac-source-c-headers)
  ;;cmd:"gcc -xc++ -E -v -" to find c/c++ header directory 
  (add-to-list 'achead:include-directories '"/usr/lib/gcc/x86_64-linux-gnu/4.8/include")
)
;;now let's call this function from c/c++ hooks
(add-hook 'c++-mode-hook 'my:ac-c-headers-init)
(add-hook 'c-mode-hook 'my:ac-c-headers-init)

;;Fix iedit bug
(define-key global-map (kbd "C-c ;") 'iedit-mode)

;;start flymake-google-cpplint-load
;;let's define a function for flymake initialization
(defun my:flymake-google-init ()
  (require 'flymake-google-cpplint)
  ;;you should install cpplint.py
  ;;$ wget http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py
  ;;$ sudo mv cpplint.py /usr/local/bin/cpplint.py
  ;;$ sudo chmod 755 /usr/local/bin/cpplint.py
  ;;You should be able to run the cpplint.py command in Emacs. If above location,
  ;;(executable-find "cpplint.py") ; => "/usr/local/bin/cpplint.py"
  (custom-set-variables
   '(flymake-google-cpplint-command "/usr/local/bin/cpplint.py"))
  (flymake-google-cpplint-load)
)
(add-hook 'c-mode-hook 'my:flymake-google-init)
(add-hook 'c++-mode-hook 'my:flymake-google-init)
;;you also can use flycheck-google-cpplint
;;from github: http://github.com/flycheck/flycheck-google-cpplint

;;then you can see red error style but have no idea
;;you should install flymake-cursor from MEPLA

;;start google-c-style with emacs
(require 'google-c-style)
(add-hook 'c-mode-common-hook 'google-set-c-style)
(add-hook 'c-mode-common-hook 'google-make-newline-indent)


;;start flycheck
(add-hook 'after-init-hook #'global-flycheck-mode)

;;turn on Semantic
(semantic-mode 1)
;;let's define a function which adds semantic as a suggestion backend to auto complete
;;and hook this function to c-mode-common-hook
(defun my:add-semantic-to-autocomplete ()
  (add-to-list 'ac-sources 'ac-source-semantic)
)
(add-hook 'c-mode-common-hook 'my:add-semantic-to-autocomplete)
;;turn on ede mode
(global-ede-mode 1)
;;create a project for our program
;;turn on automatic reparsing of open buffers in semantic
(global-semantic-idle-scheduler-mode 1)

(global-set-key (kbd "C-x C-b") 'ibuffer)
(setq-default c-basic-offset 4
	      tab-width 4
	      indent-tabs-mode t)

(column-number-mode t)
(global-set-key "\M-o" 'find-file)
(add-to-list 'load-path "~/.emacs.d/elisp")
(require 'go-mode-autoloads)

(ac-config-default)

(require 'helm-config)
(helm-mode 1)


;; Author: Patrick Gundlach 
;; nice mark - shows mark as a highlighted 'cursor' so user 'always' 
;; sees where the mark is. Especially nice for killing a region.

(defvar pg-mark-overlay nil
  "Overlay to show the position where the mark is") 
(make-variable-buffer-local 'pg-mark-overlay)

(put 'pg-mark-mark 'face 'secondary-selection)

(defvar pg-mark-old-position nil
  "The position the mark was at. To be able to compare with the
current position")

(defun pg-show-mark () 
  "Display an overlay where the mark is at. Should be hooked into 
activate-mark-hook" 
  (unless pg-mark-overlay 
    (setq pg-mark-overlay (make-overlay 0 0))
    (overlay-put pg-mark-overlay 'category 'pg-mark-mark))
  (let ((here (mark t)))
    (when here
      (move-overlay pg-mark-overlay here (1+ here)))))

(defadvice  exchange-point-and-mark (after pg-mark-exchange-point-and-mark)
  "Show visual marker"
  (pg-show-mark))

(ad-activate 'exchange-point-and-mark)
(add-hook 'activate-mark-hook 'pg-show-mark)

(defun hello ()
      "Hello World and you can call it via M-x hello."
      (interactive)
      (message "Hello World!"))


(defun multiple-hello (someone num)
      "Say hello to SOMEONE via M-x hello, for NUM times."
      (interactive "sWho do you want to say hello to? \nnHow many times? ")
      (dotimes (i num)
        (insert (format "Hello %s!\n" someone))))

(defun foo (arg buf)
    (interactive
      (list current-prefix-arg
            (read-buffer "Buffer: " (current-buffer) t)))
    ...)

(require 'cursor-chg)  ; Load the library
   (toggle-cursor-type-when-idle 1) ; Turn on cursor change when Emacs is idle
   (change-cursor-mode 1) ; Turn on change for overwrite, read-only, and input mode

(defun forward-three-chars ()
  (interactive)
  (forward-char)
  (forward-char)
  (forward-char))

(add-to-list 'load-path "~/.emacs.d/elpa")
(require 'neotree)
(global-set-key [f8] 'neotree-toggle)
