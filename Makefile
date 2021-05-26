#/ ====================================================================== BEGIN FILE =====
#/ **                                  M A K E F I L E                                  **
#/ =======================================================================================
#/ **                                                                                   **
#/ **  This file is part of the TRNCMP Research Library, `Callisto' (formerly SolLib.)  **
#/ **                                                                                   **
#/ **  Copyright (c) 2019, Stephen W. Soliday                                           **
#/ **                      stephen.soliday@trncmp.org                                   **
#/ **                      http://research.trncmp.org                                   **
#/ **                                                                                   **
#/ **  -------------------------------------------------------------------------------  **
#/ **                                                                                   **
#/ **  Callisto is free software: you can redistribute it and/or modify it under the    **
#/ **  terms of the GNU General Public License as published by the Free Software        **
#/ **  Foundation, either version 3 of the License, or (at                              **
#/ **  Callisto is distributed in the hope that it will be useful, but WITHOUT          **
#/ **  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS    **
#/ **  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.   **
#/ **                                                                                   **
#/ **  You should have received a copy of the GNU General Public License along with     **
#/ **  Callisto. If not, see <https:#/www.gnu.org/licenses/>.                           **
#/ **                                                                                   **
#/ ----- Modification History ------------------------------------------------------------
#/
#/ @brief   Build environment.
#/
#/ @details Provides a wrapper for cmake.
#/
#/ @author  Stephen W. Soliday
#/ @date    2019-Apr-18
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
	@echo "... package"
	@echo "... dpackage"
	@echo ""
.PHONY: help

DOCFLAG=OFF

TCOUNT=32

#/ =======================================================================================

debug: DEBUG
	make -j$(TCOUNT) -C $<
.PHONY: debug

DEBUG:
	mkdir -p $@/docs/media
	cp ./docs/media/* $@/docs/media/
	cd $@; cmake $(COMPILERS) -DCMAKE_BUILD_TYPE=$@ -DBUILD_DOCS=$(DOCFLAG) ..

#/ ---------------------------------------------------------------------------------------

release: RELEASE
	make -j$(TCOUNT) -C $<
.PHONY: release

RELEASE:
	mkdir -p $@/docs/media
	cp ./docs/media/* $@/docs/media/
	cd $@; cmake $(COMPILERS) -DCMAKE_BUILD_TYPE=$@ -DBUILD_DOCS=$(DOCFLAG) ..

#/ =======================================================================================

pages:
	DOCFLAG=ON make -e -C . release
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
	rm -rf scripts/__pycache__

.PHONY: distclean

#/ =======================================================================================

package: RELEASE
	make -j$(TCOUNT) -C RELEASE install
	(cd src; tar -cf - include | (cd ~; tar -xvf -))
	cp -f RELEASE/callisto/lib/libcallisto.a ~/lib/libcallisto.a
	(cd src; tar -cf - include | (cd /ARA; tar -xvf -))
	cp -f RELEASE/callisto/lib/libcallisto.a /ARA/lib/libcallisto.a


dpackage: DEBUG
	make -j$(TCOUNT) -C DEBUG install
	(cd src; tar -cf - include | (cd ~; tar -xvf -))
	cp -f DEBUG/callisto/lib/libcallisto.a ~/lib/libcallisto.a
	(cd src; tar -cf - include | (cd /ARA; tar -xvf -))
	cp -f DEBUG/callisto/lib/libcallisto.a /ARA/lib/libcallisto.a

#/ =======================================================================================
#/ **                                  M A K E F I L E                                  **
#/ =========================================================================== END FILE ==
