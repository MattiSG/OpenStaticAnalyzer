/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

package columbus.java.asg.struc;

import columbus.java.asg.expr.TypeExpression;

/**
 * Interface VariableDeclaration, which represents the {@link columbus.java.asg.struc.VariableDeclaration VariableDeclaration} node.
 * @columbus.node (missing)
 * @columbus.edge hasType ({@link columbus.java.asg.expr.TypeExpression TypeExpression}, single) : (missing)
 */
public interface VariableDeclaration extends NamedDeclaration {

	/**
	 * Gives back the reference of the node the {@link columbus.java.asg.struc.VariableDeclaration#edgeHasType hasType} edge points to.
	 * @return Returns the end point of the hasType edge.
	 */
	public TypeExpression getType();

	/**
	 * Sets the {@link columbus.java.asg.struc.VariableDeclaration#edgeHasType hasType} edge.
	 * @param id The new end point of the hasType edge.
	 */
	public void setType(int id);

	/**
	 * Sets the {@link columbus.java.asg.struc.VariableDeclaration#edgeHasType hasType} edge.
	 * @param node The new end point of the hasType edge.
	 */
	public void setType(TypeExpression node);

}

