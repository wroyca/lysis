# liblysis - A C++ library

The `liblysis` C++ library provides <SUMMARY-OF-FUNCTIONALITY>.


## Usage

To start using `liblysis` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: liblysis ^<VERSION>
```

Then import the library in your `buildfile`:

```
import libs = liblysis%lib{<TARGET>}
```


## Importable targets

This package provides the following importable targets:

```
lib{<TARGET>}
```

<DESCRIPTION-OF-IMPORTABLE-TARGETS>


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.liblysis.<VARIABLE> ?= false
```

<DESCRIPTION-OF-CONFIG-VARIABLES>
