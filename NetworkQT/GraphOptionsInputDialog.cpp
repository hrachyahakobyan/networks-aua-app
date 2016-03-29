#include "stdafx.h"
#include "GraphOptionsInputDialog.h"

GraphOptionsInputDialog::GraphOptionsInputDialog(QWidget *parent, const std::string& type)
	: MultiInputDialog(parent), type_(type)
{
	if (type_.compare(GRAPH_BINOMIAL) == 0)
	{
		addInputs(QList<QString>({ "Height" }));
	}
	else if (type_.compare(GRAPH_COMPLETE) == 0)
	{
		addInputs(QList<QString>({ "Vertices" }));
	}
	else if (type_.compare(GRAPH_HYPER) == 0)
	{
		addInputs(QList<QString>({ "Dimension" }));
	}
	else if (type_.compare(GRAPH_KNODEL) == 0)
	{
		addInputs(QList<QString>({ "Vertices" }));
	}
	else if (type_.compare(GRAPH_KTREE) == 0)
	{
		addInputs(QList<QString>({ "Height" }));
		addInputs(QList<QString>({ "K" }));
	}
	else
	{
		assert(false && "ERROR: GraphOptionsInputDialog: unknown graph type \n");
	}
	for each (QLineEdit* line in lines_)
	{
		line->setValidator(new QIntValidator(1, 30, this));
	}
}

GraphOptionsInputDialog::~GraphOptionsInputDialog()
{

}

bool GraphOptionsInputDialog::validate()
{
	if (type_.compare(GRAPH_BINOMIAL) == 0)
	{
		assert(inputs_map_.find("Height") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		QString h_string = inputs_map_["Height"];
		bool b_h;
		int height = h_string.toInt(&b_h);
		if (b_h)
		{
			if (height > 0 && height <= GRAPH_BINOMIAL_MAX_HEIGHT)
				return true;
			return false;
		}
		return false;
	}
	else if (type_.compare(GRAPH_COMPLETE) == 0)
	{
		assert(inputs_map_.find("Vertices") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		QString v_string = inputs_map_["Vertices"];
		bool b_v;
		int vertices = v_string.toInt(&b_v);
		if (b_v)
		{
			if (vertices > 0 && vertices <= GRAPH_COMPLETE_MAX_VERTICES)
			{
				return true;
			}
			return false;

		}
		return false;
	}
	else if (type_.compare(GRAPH_HYPER) == 0)
	{
		assert(inputs_map_.find("Dimension") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		QString d_string = inputs_map_["Dimension"];
		bool b_d;
		int dim = d_string.toInt(&b_d);
		if (b_d)
		{
			if (dim > 0 && dim <= GRAPH_HYPER_MAX_DIM)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	else if (type_.compare(GRAPH_KNODEL) == 0)
	{
		assert(inputs_map_.find("Vertices") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		QString v_string = inputs_map_["Vertices"];
		bool b_v;
		int vertices = v_string.toInt(&b_v);
		if (b_v)
		{
			if (vertices > 0 && vertices <= GRAPH_KNODEL_MAX_VERTICES && vertices % 2 == 0)
			{
				return true;
			}
			return false;

		}
		return false;
	}
	else if (type_.compare(GRAPH_KTREE) == 0)
	{
		assert(inputs_map_.find("Height") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		assert(inputs_map_.find("K") != inputs_map_.end() && "ERROR: GraphOptionsInputDialog: Inputs do not contain required input");
		QString h_string = inputs_map_["Height"];
		QString k_string = inputs_map_["K"];
		bool b_h, b_k;
		int height = h_string.toInt(&b_h);
		int k = k_string.toInt(&b_k);
		if (b_h && b_k)
		{
			if (height > 0 && k > 0)
			{
				if ((int(std::pow(k, height + 1)) - 1) / (k - 1) < GRAPH_KTREE_MAX_VERTICES)
				{
					return true;
				}
				return false;
			}
			return false;
		}
	}
	return false;
}

// Slots

void GraphOptionsInputDialog::okButtonClicked()
{
	options_.type_ = type_;
	if (inputs_map_.find("Height") != inputs_map_.end())
		options_.height_ = inputs_map_["Height"].toInt();
	if (inputs_map_.find("K") != inputs_map_.end())
		options_.k_ = inputs_map_["K"].toInt();
	if (inputs_map_.find("Vertices") != inputs_map_.end())
		options_.n_vertices_ = inputs_map_["Vertices"].toInt();
	if (inputs_map_.find("Dimension") != inputs_map_.end())
		options_.dim_ = inputs_map_["Dimension"].toInt();
	accept();
}

void GraphOptionsInputDialog::cancelButtonClicked()
{
	reject();
}

void GraphOptionsInputDialog::reject()
{
	Q_EMIT finishedInput(QDialog::Rejected, options_);
	QDialog::reject();
}


void GraphOptionsInputDialog::accept()
{
	Q_EMIT finishedInput(QDialog::Accepted, options_);
	QDialog::reject();
}



