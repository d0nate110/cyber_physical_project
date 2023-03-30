#!/bin/sh

if expr match "$CI_COMMIT_TAG" "^v[0-9]\.[0-9]\.[0-9]$"; then
    echo "Versioned correctly. Onward ...";
else
    echo "Invalid versioning."
    return 1;
fi;
