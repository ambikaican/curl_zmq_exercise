{
  "nbformat": 4,
  "nbformat_minor": 0,
  "metadata": {
    "colab": {
      "name": "fastai_base.ipynb",
      "provenance": [],
      "authorship_tag": "ABX9TyP0byKh9eqZnS7r37qO6J98",
      "include_colab_link": true
    },
    "kernelspec": {
      "name": "python3",
      "display_name": "Python 3"
    },
    "language_info": {
      "name": "python"
    }
  },
  "cells": [
    {
      "cell_type": "markdown",
      "metadata": {
        "id": "view-in-github",
        "colab_type": "text"
      },
      "source": [
        "<a href=\"https://colab.research.google.com/github/ambikaican/curl_zmq_exercise/blob/master/fastai_base.ipynb\" target=\"_parent\"><img src=\"https://colab.research.google.com/assets/colab-badge.svg\" alt=\"Open In Colab\"/></a>"
      ]
    },
    {
      "cell_type": "code",
      "source": [
        "#!pip install flask_cors"
      ],
      "metadata": {
        "colab": {
          "base_uri": "https://localhost:8080/"
        },
        "id": "z32FmZLq5d2o",
        "outputId": "3d195ebb-7791-466d-a4c3-2b3af05203b1"
      },
      "execution_count": 12,
      "outputs": [
        {
          "output_type": "stream",
          "name": "stdout",
          "text": [
            "Collecting flask_cors\n",
            "  Downloading Flask_Cors-3.0.10-py2.py3-none-any.whl (14 kB)\n",
            "Requirement already satisfied: Six in /usr/local/lib/python3.7/dist-packages (from flask_cors) (1.15.0)\n",
            "Requirement already satisfied: Flask>=0.9 in /usr/local/lib/python3.7/dist-packages (from flask_cors) (1.1.4)\n",
            "Requirement already satisfied: click<8.0,>=5.1 in /usr/local/lib/python3.7/dist-packages (from Flask>=0.9->flask_cors) (7.1.2)\n",
            "Requirement already satisfied: itsdangerous<2.0,>=0.24 in /usr/local/lib/python3.7/dist-packages (from Flask>=0.9->flask_cors) (1.1.0)\n",
            "Requirement already satisfied: Jinja2<3.0,>=2.10.1 in /usr/local/lib/python3.7/dist-packages (from Flask>=0.9->flask_cors) (2.11.3)\n",
            "Requirement already satisfied: Werkzeug<2.0,>=0.15 in /usr/local/lib/python3.7/dist-packages (from Flask>=0.9->flask_cors) (1.0.1)\n",
            "Requirement already satisfied: MarkupSafe>=0.23 in /usr/local/lib/python3.7/dist-packages (from Jinja2<3.0,>=2.10.1->Flask>=0.9->flask_cors) (2.0.1)\n",
            "Installing collected packages: flask-cors\n",
            "Successfully installed flask-cors-3.0.10\n"
          ]
        }
      ]
    },
    {
      "cell_type": "code",
      "execution_count": 15,
      "metadata": {
        "id": "GmZqYe2wwc6F"
      },
      "outputs": [],
      "source": [
        "from flask import Flask, request, jsonify\n",
        "from fastai.basic_train import load_learner\n",
        "from fastai.vision import open_image\n",
        "\n",
        "from __future__ import print_function\n",
        "from ipywidgets import interact, interactive, fixed, interact_manual\n",
        "import ipywidgets\n",
        "import ipywidgets as widgets\n",
        "from IPython.display import display,clear_output\n",
        "\n",
        "import pandas as pd\n",
        "\n",
        "from fastai.vision import *\n",
        "from fastai.widgets import *\n",
        "from fastai.callbacks import*\n",
        "from fastai.widgets import ClassConfusion\n",
        "\n",
        "import matplotlib.pyplot as plt\n",
        "\n",
        "from tkinter import Tk\n",
        "from tkinter import filedialog\n",
        "from tkinter.filedialog import askdirectory\n",
        "\n",
        "import webbrowser"
      ]
    },
    {
      "cell_type": "code",
      "source": [
        "#widget layouts\n",
        "layout = {'width':'90%', 'height': '50px', 'border': 'solid', 'fontcolor':'lightgreen'}\n",
        "layout_two = {'width':'100px', 'height': '200px', 'border': 'solid', 'fontcolor':'lightgreen'}\n",
        "style_green = {'handle_color': 'green', 'readout_color': 'red', 'slider_color': 'blue'}\n",
        "style_blue = {'handle_color': 'blue', 'readout_color': 'red', 'slider_color': 'blue'}\n"
      ],
      "metadata": {
        "id": "R0J-j7xl12Bo"
      },
      "execution_count": 2,
      "outputs": []
    },
    {
      "cell_type": "code",
      "source": [
        "def gui1():\n",
        "  button = widgets.Button(description='Data Analayis - EDA ')\n",
        "  display(button)\n",
        "\n",
        "  out = widgets.Output()\n",
        "  display(out)\n",
        "\n",
        "  def on_button_clicked_info(b):\n",
        "      with out:\n",
        "            clear_output()\n",
        "            print(\"EDA\")  \n",
        "  button.on_click(on_button_clicked_info)\n"
      ],
      "metadata": {
        "id": "tqQu6ZG92AWL"
      },
      "execution_count": 13,
      "outputs": []
    },
    {
      "cell_type": "markdown",
      "source": [
        "from flask_cors import CORS,cross_origin\n",
        "\n",
        "app = Flask(__name__)\n",
        "CORS(app, support_credentials=True)\n",
        "\n",
        "def predict_single(img_file):\n",
        "    gui1()\n",
        "\n",
        "# route for prediction\n",
        "@app.route('/predict', methods=['POST'])\n",
        "def predict():\n",
        "    return jsonify(predict_single(request.files['image']))\n",
        "\n",
        "if __name__ == '__main__':\n",
        "    app.run()"
      ],
      "metadata": {
        "id": "USaxDSS679gv"
      }
    },
    {
      "cell_type": "code",
      "source": [
        ""
      ],
      "metadata": {
        "colab": {
          "base_uri": "https://localhost:8080/"
        },
        "id": "eYBIv5ou5ael",
        "outputId": "85987e8f-6e80-4f2f-c734-5878419c88bc"
      },
      "execution_count": 16,
      "outputs": [
        {
          "output_type": "stream",
          "name": "stdout",
          "text": [
            " * Serving Flask app \"__main__\" (lazy loading)\n",
            " * Environment: production\n",
            "\u001b[31m   WARNING: This is a development server. Do not use it in a production deployment.\u001b[0m\n",
            "\u001b[2m   Use a production WSGI server instead.\u001b[0m\n",
            " * Debug mode: off\n"
          ]
        },
        {
          "output_type": "stream",
          "name": "stderr",
          "text": [
            " * Running on http://127.0.0.1:5000/ (Press CTRL+C to quit)\n"
          ]
        }
      ]
    }
  ]
}
