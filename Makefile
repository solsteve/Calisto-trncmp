#/ ====================================================================== BEGIN FILE =====
#/ **                                  M A K E F I L E                                  **
#/ =======================================================================================
#/ **                                                                                   **
#/ **  Copyright (c) 2019, Stephen W. Soliday                                           **
#/ **                      stephen.soliday@trncmp.org                                   **
#/ **                      http://research.trncmp.org                                   **
#/ **                                                                                   **
#/ **  -------------------------------------------------------------------------------  **
#/ **                                                                                   **
#/ **  This program is free software: you can redistribute it and/or modify it under    **
#/ **  the terms of the GNU General Public License as published by the Free Software    **
#/ **  Foundation, either version 3 of the License, or (at your option)                 **
#/ **  any later version.                                                               **
#/ **                                                                                   **
#/ **  This program is distributed in the hope that it will be useful, but WITHOUT      **
#/ **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
#/ **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
#/ **                                                                                   **
#/ **  You should have received a copy of the GNU General Public License along with     **
#/ **  this program. If not, see <http://www.gnu.org/licenses/>.                        **
#/ **                                                                                   **
#/ ----- Modification History ------------------------------------------------------------
#/
#/ @details Provides a wrapper for cmake.
#/
#/ @author  Stephen W. Soliday
#/ @date    2019-04-11
#/
#/ =======================================================================================

all: debug
.PHONY: all

help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... debug"
	@echo "... release"
	@echo "... pages (builds doxygen documents)"
	@echo "... clean"
	@echo "... fullclean"
	@echo "... distclean"
	@echo ""
.PHONY: help

BUILD_DOCS=OFF

#/ =======================================================================================

debug: DEBUG
	make -C $<
.PHONY: debug

DEBUG:
	mkdir -p $@/docs/media
	cp ./docs/media/* $@/docs/media/
	cd $@; cmake $(COMPILERS) -DCMAKE_BUILD_TYPE=$@ -DBUILD_DOCS=$(DOCFLAG) ..

#/ ---------------------------------------------------------------------------------------

release: RELEASE
	make -C $<
.PHONY: release

RELEASE:
	mkdir -p $@/docs/media
	cp ./docs/media/* $@/docs/media/
	cd $@; cmake $(COMPILERS) -DCMAKE_BUILD_TYPE=$@ -DBUILD_DOCS=$(DOCFLAG) ..

#/ =======================================================================================

pages:
	BUILD_DOCS=ON make -e -C . release
.PHONY: pages

#/ =======================================================================================

clean:
	@echo "Done..." $@
.PHONY: clean

fullclean: clean
	rm -rf RELEASE DEBUG
	rm -rf docs/html docs/latex docs/man
.PHONY: fullclean

distclean: fullclean
	find . -name "*~" | xargs rm -f
.PHONY: distclean

#/ =======================================================================================
#/ **                                  M A K E F I L E                                  **
#/ =========================================================================== END FILE ==
