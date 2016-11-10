try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

config = {
    'description' : 'My Project',
    'author' : 'Ynhan',
    'url' : 'URL to get it at.',
    'download_url' : 'where to download',
    'author_email' : 'physhouse@gmail.com',
    'version' : '0.1',
    'install_requires' : ['noe'],
    'packages' : ['ynhan'],
    'scripts': [],
    'name' : 'projectname'
}

setup(**config)
