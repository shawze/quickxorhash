from distutils.core import setup, Extension

setup(
    name='quickxorhash',
    version = '1.0.1',
    description='Quick XOR hash function for OneDrive for Business',
    long_description='',
    keywords='quickxorhash onedrive',
    license='MIT',
    author='Harry Chen',
    author_email='cjhecm@gmail.com',
    url='https://github.com/HarryChen/quickxorhash',
    ext_modules=[
        Extension('quickxorhash', ['module.c', 'quickxorhash.c'])
    ],
    classifiers=[
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
        'Programming Language :: Python',
        'Topic :: Software Development :: Libraries :: Python Modules',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: Implementation :: CPython',
        'Development Status :: 4 - Beta',
    ],
)
