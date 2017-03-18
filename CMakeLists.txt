cmake_minimum_required(VERSION 3.0)



#Configuration du projet
project(ModelisationL3)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})


#Generation de la liste des fichiers sources
file(
	GLOB_RECURSE
	source_files
	src/*
)

#Declaration de l'executable
add_executable(
	ModelisationL3
	${source_files}
)

target_compile_features(ModelisationL3 PRIVATE cxx_range_for)