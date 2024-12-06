project('simulaRU', 'c',
    version: '0.1',
    default_options: [
        'c_std=gnu17',
    ],
    license: 'MIT'
)

cc = meson.get_compiler('c')

m_dep = cc.find_library('m', required: true)

inc = include_directories('include')

obj_sources = files(
    'src/bancada.c',
    'src/descanso.c',
    'src/fila.c',
    'src/ingrediente.c',
    'src/log.c',
    'src/rando.c',
    'src/relatorio.c',
    'src/relogio.c',
    'src/restaurante.c',
    'src/servente.c',
    'src/usuario.c',
    'src/vasilha.c',
)

#subdir('test')

executable(
    meson.project_name(),
    obj_sources,
    'src/main.c',
    include_directories: inc,
    dependencies: m_dep,
)
