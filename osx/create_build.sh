#!/bin/bash

cp debug/ASTRO ASTRO.app/Contents/MacOS/.
cp -a ../Game/astro/* ASTRO.app/Contents/Resources/astro/.
zip -r ASTRO.zip ASTRO.app/