find_program(GLSLANG_VALIDATOR NAMES glslangValidator
    HINTS "$ENV{VULKAN_SDK}/bin"
)

if(NOT GLSLANG_VALIDATOR)
    message(FATAL_ERROR "glslangValidator not found. Set VULKAN_SDK.")
endif()

set(SHADER_DIR ${CMAKE_SOURCE_DIR}/shaders)
set(SPIRV_DIR ${CMAKE_BINARY_DIR}/shaders)

file(MAKE_DIRECTORY ${SPIRV_DIR})

file(GLOB SHADER_SOURCES
    "${SHADER_DIR}/*.vert"
    "${SHADER_DIR}/*.frag"
    "${SHADER_DIR}/*.comp"
)

set(SPIRV_OUTPUTS)

foreach(shader ${SHADER_SOURCES})
    get_filename_component(name ${shader} NAME)
    set(output "${SPIRV_DIR}/${name}.spv")

    add_custom_command(
        OUTPUT ${output}
        COMMAND ${GLSLANG_VALIDATOR} -V ${shader} -o ${output}
        DEPENDS ${shader}
        COMMENT "Compiling shader: ${name}"
    )

    list(APPEND SPIRV_OUTPUTS ${output})
endforeach()

add_custom_target(shaders ALL DEPENDS ${SPIRV_OUTPUTS})