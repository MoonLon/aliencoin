from distutils.core import setup
setup(name='ALCspendfrom',
      version='1.0',
      description='Command-line utility for aliencoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@aliencoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
