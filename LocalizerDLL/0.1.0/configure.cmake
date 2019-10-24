# Configuration for package "LocalizerDLL"

set( LOCALIZERDLL_MAJOR_VERSION	0 )
set( LOCALIZERDLL_MINOR_VERSION	1 )
set( LOCALIZERDLL_PATCH_VERSION	0 )

set( LOCALIZERDLL_INCLUDE	$ENV{MEDITEC_LIBS}/LocalizerDLL/0.1.0/include )
set( LOCALIZERDLL_LIBDIR	$ENV{MEDITEC_LIBS}/LocalizerDLL/0.1.0/bin )
set( LOCALIZERDLL_LIBLIST
		optimized	LocalizerDLL-0.1.0
		debug		LocalizerDLL-0.1.0d
	)
		
include_directories( ${LOCALIZERDLL_INCLUDE} )
link_directories( ${LOCALIZERDLL_LIBDIR} )

include( $ENV{MEDITEC_LIBS}/MathBib/0.1.0/configure.cmake )
