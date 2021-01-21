## Doxygen-github-action-demo

# Doxygen Documentation
[Documentation](https://josephwhittington.github.io/documentation-test/)

## Main action workflow configuration
```yml
### Main.yml
# This is a basic workflow to help you get started with Actions

name: Doxygen Action

# Controls when the action will run. Triggers the workflow on push or pull request
# events but only for the master branch
on:
  push:
    branches: [ master ]
  pull_request:
    branches: [ master ]


  
# A workflow run is made up of one or more jobs that can run sequentially or in parallel
jobs:
  # This workflow contains a single job called "build"
  build:
    # The type of runner that the job will run on
    runs-on: ubuntu-latest

    # Steps represent a sequence of tasks that will be executed as part of the job
    steps:
    # Checks-out your repository under $GITHUB_WORKSPACE, so your job can access it
    - uses: actions/checkout@v2
        
    - name: Doxygen Action
      uses: mattnotmitt/doxygen-action@v1.1.0
      with:
        # Path to Doxyfile
        doxyfile-path: "./Doxyfile" # default is ./Doxyfile
        # Working directory
    
    - name: Deploy
      uses: peaceiris/actions-gh-pages@v3
      with:
        github_token: ${{ secrets.GITHUB_TOKEN }}
        publish_dir: ./html
```