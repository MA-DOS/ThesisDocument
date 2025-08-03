#!/bin/bash
URL="https://api.citedrive.com/bib/9b9446ad-90b6-4683-a87a-dcb5b6b1bc41/references.bib?x=eyJpZCI6ICI5Yjk0NDZhZC05MGI2LTQ2ODMtYTg3YS1kY2I1YjZiMWJjNDEiLCAidXNlciI6ICIxNjI2OSIsICJzaWduYXR1cmUiOiAiNDlkNjZjMDcxY2Q5NmRkZjIzZmZmNjU5NGVkYzUxZjcxM2FjZjI3NDFhZjA4YTUyNzJkNDkyZjVlZjU2MTMyMiJ9"
curl "$URL" > "./references.bib"